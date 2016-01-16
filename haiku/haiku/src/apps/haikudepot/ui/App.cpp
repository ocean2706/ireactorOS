/*
 * Copyright 2013, Stephan Aßmus <superstippi@gmx.de>.
 * All rights reserved. Distributed under the terms of the MIT License.
 */


#include "App.h"

#include <stdio.h>

#include <Alert.h>
#include <Catalog.h>
#include <Entry.h>
#include <Message.h>
#include <package/PackageInfo.h>
#include <Path.h>
#include <Roster.h>
#include <Screen.h>
#include <String.h>

#include "support.h"

#include "FeaturedPackagesView.h"
#include "MainWindow.h"


#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "App"


App::App()
	:
	BApplication("application/x-vnd.Haiku-HaikuDepot"),
	fMainWindow(NULL),
	fWindowCount(0),
	fSettingsRead(false)
{
	_CheckPackageDaemonRuns();
}


App::~App()
{
	// We cannot let global destructors cleanup static BitmapRef objects,
	// since calling BBitmap destructors needs a valid BApplication still
	// around. That's why we do it here.
	PackageInfo::CleanupDefaultIcon();
	FeaturedPackagesView::CleanupIcons();
}


bool
App::QuitRequested()
{
	if (fMainWindow != NULL
		&& fMainWindow->LockLooperWithTimeout(1500000) == B_OK) {
		BMessage windowSettings;
		fMainWindow->StoreSettings(windowSettings);

		fMainWindow->UnlockLooper();

		_StoreSettings(windowSettings);
	}

	return true;
}


void
App::ReadyToRun()
{
	if (fWindowCount > 0)
		return;

	BMessage settings;
	_LoadSettings(settings);

	fMainWindow = new MainWindow(settings);
	_ShowWindow(fMainWindow);
}


void
App::MessageReceived(BMessage* message)
{
	switch (message->what) {
		case MSG_MAIN_WINDOW_CLOSED:
		{
			BMessage windowSettings;
			if (message->FindMessage("window settings",
					&windowSettings) == B_OK) {
				_StoreSettings(windowSettings);
			}

			fWindowCount--;
			if (fWindowCount == 0)
				Quit();
			break;
		}

		default:
			BApplication::MessageReceived(message);
			break;
	}
}


void
App::RefsReceived(BMessage* message)
{
	entry_ref ref;
	int32 index = 0;
	while (message->FindRef("refs", index++, &ref) == B_OK) {
		BEntry entry(&ref, true);
		_Open(entry);
	}
}


void
App::ArgvReceived(int32 argc, char* argv[])
{
	for (int i = 1; i < argc;) {
		if (0 == strcmp("--webappbaseurl", argv[i])) {
			if (i == argc-1) {
				fprintf(stderr, "unexpected end of arguments; missing web app base url\n");
				Quit();
			}

			if (WebAppInterface::SetBaseUrl(argv[i + 1]) != B_OK) {
				fprintf(stderr, "malformed web app base url; %s\n", argv[i + 1]);
				Quit();
			}
			else
				fprintf(stderr, "did configure the web base url; %s\n",argv[i + 1]);

			i += 2;
		} else {
			BEntry entry(argv[i], true);
			_Open(entry);
			i++;
		}
	}
}


// #pragma mark - private


void
App::_Open(const BEntry& entry)
{
	BPath path;
	if (!entry.Exists() || !entry.GetPath(&path) == B_OK) {
		fprintf(stderr, "Package file not found: %s\n", path.Path());
		return;
	}

	// Try to parse package file via Package Kit
	BPackageKit::BPackageInfo info;
	status_t status = info.ReadFromPackageFile(path.Path());
	if (status != B_OK) {
		fprintf(stderr, "Failed to parse package file: %s\n",
			strerror(status));
		return;
	}

	// Transfer information into PackageInfo
	PackageInfoRef package(new(std::nothrow) PackageInfo(info), true);
	if (package.Get() == NULL) {
		fprintf(stderr, "Could not allocate PackageInfo\n");
		return;
	}

	package->SetLocalFilePath(path.Path());

	BMessage settings;
	_LoadSettings(settings);

	MainWindow* window = new MainWindow(settings, package);
	_ShowWindow(window);
}


void
App::_ShowWindow(MainWindow* window)
{
	window->Show();
	fWindowCount++;
}


bool
App::_LoadSettings(BMessage& settings)
{
	if (!fSettingsRead) {
		fSettings = true;
		if (load_settings(&fSettings, "main_settings", "HaikuDepot") != B_OK)
			fSettings.MakeEmpty();
	}
	settings = fSettings;
	return !fSettings.IsEmpty();
}


void
App::_StoreSettings(const BMessage& settings)
{
	// Take what is in settings and replace data under the same name in
	// fSettings, leaving anything in fSettings that is not contained in
	// settings.
	int32 i = 0;

	char* name;
	type_code type;
	int32 count;

	while (settings.GetInfo(B_ANY_TYPE, i++, &name, &type, &count) == B_OK) {
		fSettings.RemoveName(name);
		for (int32 j = 0; j < count; j++) {
			const void* data;
			ssize_t size;
			if (settings.FindData(name, type, j, &data, &size) != B_OK)
				break;
			fSettings.AddData(name, type, data, size);
		}
	}

	save_settings(&fSettings, "main_settings", "HaikuDepot");
}


// #pragma mark -


static const char* kPackageDaemonSignature
	= "application/x-vnd.haiku-package_daemon";

void
App::_CheckPackageDaemonRuns()
{
	while (!be_roster->IsRunning(kPackageDaemonSignature)) {
		BAlert* alert = new BAlert("start_package_daemon",
			B_TRANSLATE("HaikuDepot needs the package daemon to function, "
				"and it appears to be not running.\n"
				"Would you like to start it now?"),
			B_TRANSLATE("No, quit HaikuDepot"),
			B_TRANSLATE("Start package daemon"), NULL, B_WIDTH_AS_USUAL,
			B_WARNING_ALERT);
		alert->SetShortcut(0, B_ESCAPE);

		if (alert->Go() == 0)
			exit(1);

		if (!_LaunchPackageDaemon())
			break;
	}
}


bool
App::_LaunchPackageDaemon()
{
	status_t ret = be_roster->Launch(kPackageDaemonSignature);
	if (ret != B_OK) {
		BString errorMessage
			= B_TRANSLATE("Starting the package daemon failed:\n\n%Error%");
		errorMessage.ReplaceAll("%Error%", strerror(ret));

		BAlert* alert = new BAlert("package_daemon_problem",
			errorMessage,
			B_TRANSLATE("Quit HaikuDepot"),
			B_TRANSLATE("Try again"), NULL, B_WIDTH_AS_USUAL,
			B_WARNING_ALERT);
		alert->SetShortcut(0, B_ESCAPE);

		if (alert->Go() == 0)
			return false;
	}
	// TODO: Would be nice to send a message to the package daemon instead
	// and get a reply once it is ready.
	snooze(2000000);
	return true;
}

