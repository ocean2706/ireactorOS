/*
 * Copyright 2014, Stephan Aßmus <superstippi@gmx.de>.
 * All rights reserved. Distributed under the terms of the MIT License.
 */
#ifndef RATE_PACKAGE_WINDOW_H
#define RATE_PACKAGE_WINDOW_H

#include <Window.h>

#include "Model.h"
#include "PackageInfo.h"
#include "TextDocument.h"
#include "TextEditor.h"


class BButton;
class BCheckBox;
class BMenuField;
class SetRatingView;
class TextDocumentView;


class RatePackageWindow : public BWindow {
public:
								RatePackageWindow(BWindow* parent, BRect frame,
									Model& model);
	virtual						~RatePackageWindow();

	virtual	void				MessageReceived(BMessage* message);

			void				SetPackage(const PackageInfoRef& package);

private:
			void				_SendRating();

			void				_SetWorkerThread(thread_id thread);

	static	int32				_QueryRatingThreadEntry(void* data);
			void				_QueryRatingThread();

	static	int32				_SendRatingThreadEntry(void* data);
			void				_SendRatingThread();

private:
			Model&				fModel;
			TextDocumentRef		fRatingText;
			TextEditorRef		fTextEditor;
			float				fRating;
			BString				fStability;
			StabilityRatingList	fStabilityCodes;
			BString				fCommentLanguage;
			BString				fRatingID;
			bool				fRatingActive;
			PackageInfoRef		fPackage;

			SetRatingView*		fSetRatingView;
			BMenuField*			fStabilityField;
			BMenuField*			fCommentLanguageField;
			TextDocumentView*	fTextView;
			BCheckBox*			fRatingActiveCheckBox;
			BButton*			fCancelButton;
			BButton*			fSendButton;

			thread_id			fWorkerThread;
};


#endif // RATE_PACKAGE_WINDOW_H
