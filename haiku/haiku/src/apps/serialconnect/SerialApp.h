/*
 * Copyright 2012, Adrien Destugues, pulkomandy@gmail.com
 * Distributed under the terms of the MIT licence.
 */


#ifndef _SERIALAPP_H_
#define _SERIALAPP_H_


#include <Application.h>
#include <PropertyInfo.h>
#include <SerialPort.h>
#include <String.h>


class BFile;
class SerialWindow;


class SerialApp: public BApplication
{
	public:
							SerialApp();
							~SerialApp();
				void		ReadyToRun();
				void		MessageReceived(BMessage* message);
				bool		QuitRequested();

				status_t	GetSupportedSuites(BMessage* message);
				BHandler*	ResolveSpecifier(BMessage*, int32, BMessage*, int32,
								const char*);

		const	BString&	GetPort();

	private:
				void		LoadSettings();
				void		SaveSettings();

	private:
						BSerialPort		fSerialPort;
						sem_id			fSerialLock;
						SerialWindow*	fWindow;
						BFile*			fLogFile;
						BString			fPortPath;

		static			status_t		PollSerial(void*);

		static const	BPropertyInfo	kScriptingProperties;
		static const	char*			kApplicationSignature;
};


enum messageConstants {
	kMsgDataRead  = 'dare',
	kMsgDataWrite = 'dawr',
	kMsgLogfile   = 'logf',
	kMsgOpenPort  = 'open',
	kMsgSettings  = 'stty',
};

#endif
