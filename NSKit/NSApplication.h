//
//  NSApplication.h
//  NSKit
//
//  Created by Sterling  on 11/10/2016.
//  Copyright © 2016 TheHitherGuy. All rights reserved.
//

#import <UIKit/UIKit.h>
@protocol NSApplicationDelegate;
@interface NSApplication : UIApplication

+ (__kindof NSApplication *)sharedApplication;
@property (nullable, assign) id<NSApplicationDelegate> delegate;
//@property (nullable, readonly, strong) NSGraphicsContext *context;
- (void)hide:(nullable id)sender;
- (void)unhide:(nullable id)sender;
- (void)unhideWithoutActivation;
- (nullable NSWindow *)windowWithWindowNumber:(NSInteger)windowNum;
@property (nullable, readonly, assign) NSWindow *mainWindow;
@property (nullable, readonly, assign) NSWindow *keyWindow;
@property (getter=isActive, readonly) BOOL active;
@property (getter=isHidden, readonly) BOOL hidden;
@property (getter=isRunning, readonly) BOOL running;
- (void)deactivate;
- (void)activateIgnoringOtherApps:(BOOL)flag;

- (void)hideOtherApplications:(nullable id)sender;
- (void)unhideAllApplications:(nullable id)sender;

- (void)finishLaunching;
- (void)run;
- (NSInteger)runModalForWindow:(NSWindow *)theWindow;
- (void)stop:(nullable id)sender;
- (void)stopModal;
- (void)stopModalWithCode:(NSInteger)returnCode;
- (void)abortModal;
@property (nullable, readonly, strong) NSWindow *modalWindow;
//- (NSModalSession)beginModalSessionForWindow:(NSWindow *)theWindow NS_RETURNS_INNER_POINTER;
//- (NSInteger)runModalSession:(NSModalSession)session;
//- (void)endModalSession:(NSModalSession)session;
- (void)terminate:(nullable id)sender;

typedef NS_ENUM(NSUInteger, NSRequestUserAttentionType) {
    NSCriticalRequest = 0,
    NSInformationalRequest = 10
};

// inform the user that this application needs attention - call this method only if your application is not already active
- (NSInteger)requestUserAttention:(NSRequestUserAttentionType)requestType;
- (void)cancelUserAttentionRequest:(NSInteger)request;


- (nullable NSEvent *)nextEventMatchingMask:(NSUInteger)mask untilDate:(nullable NSDate *)expiration inMode:(NSString *)mode dequeue:(BOOL)deqFlag;
- (void)discardEventsMatchingMask:(NSUInteger)mask beforeEvent:(nullable NSEvent *)lastEvent;
- (void)postEvent:(NSEvent *)event atStart:(BOOL)flag;
@property (nullable, readonly, strong) NSEvent *currentEvent;

- (void)sendEvent:(NSEvent *)theEvent;
- (void)preventWindowOrdering;
- (nullable NSWindow *)makeWindowsPerform:(SEL)aSelector inOrder:(BOOL)flag;
@property (readonly, copy) NSArray<NSWindow *> *windows;
- (void)setWindowsNeedUpdate:(BOOL)needUpdate;
- (void)updateWindows;

@property (nullable, strong) NSMenu *mainMenu;

/* Set or get the Help menu for the app.  If a non-nil menu is set as the Help menu, Spotlight for Help will be installed in it; otherwise AppKit will install Spotlight for Help into a menu of its choosing (and that menu is not returned from -helpMenu).  If you wish to completely suppress Spotlight for Help, you can set a menu that does not appear in the menu bar.  NSApplication retains its Help menu and releases it when a different menu is set.
 
 */
@property (nullable, strong) NSMenu *helpMenu NS_AVAILABLE_MAC(10_6);

@property (null_resettable, strong) NSImage *applicationIconImage;

/* Returns the activation policy of the application.
 */
//- (NSApplicationActivationPolicy)activationPolicy NS_AVAILABLE_MAC(10_6);

/* Attempts to modify the application's activation policy.  In OS X 10.9, any policy may be set; prior to 10.9, the activation policy may be changed to NSApplicationActivationPolicyProhibited or NSApplicationActivationPolicyRegular, but may not be changed to NSApplicationActivationPolicyAccessory.  This returns YES if setting the activation policy is successful, and NO if not.
 */
//- (BOOL)setActivationPolicy:(NSApplicationActivationPolicy)activationPolicy NS_AVAILABLE_MAC(10_6);


//@property (readonly, strong) NSDockTile *dockTile NS_AVAILABLE_MAC(10_5);

- (BOOL)sendAction:(SEL)theAction to:(nullable id)theTarget from:(nullable id)sender;
- (nullable id)targetForAction:(SEL)theAction;
- (nullable id)targetForAction:(SEL)theAction to:(nullable id)theTarget from:(nullable id)sender;
- (BOOL)tryToPerform:(SEL)anAction with:(nullable id)anObject;
- (nullable id)validRequestorForSendType:(NSString *)sendType returnType:(NSString *)returnType;

- (void)reportException:(NSException *)theException;
+ (void)detachDrawingThread:(SEL)selector toTarget:(id)target withObject:(nullable id)argument;

/*  If an application delegate returns NSTerminateLater from -applicationShouldTerminate:, -replyToApplicationShouldTerminate: must be called with YES or NO once the application decides if it can terminate */
- (void)replyToApplicationShouldTerminate:(BOOL)shouldTerminate;

typedef NS_ENUM(NSUInteger, NSApplicationDelegateReply) {
    NSApplicationDelegateReplySuccess = 0,
    NSApplicationDelegateReplyCancel = 1,
    NSApplicationDelegateReplyFailure = 2
};

/* If an application delegate encounters an error while handling -application:openFiles: or -application:printFiles:, -replyToOpenOrPrint: should be called with NSApplicationDelegateReplyFailure.  If the user cancels the operation, NSApplicationDelegateReplyCancel should be used, and if the operation succeeds, NSApplicationDelegateReplySuccess should be used */
- (void)replyToOpenOrPrint:(NSApplicationDelegateReply)reply;

/* Opens the character palette
 */
- (void)orderFrontCharacterPalette:(nullable id)sender;

/* Gets or sets the presentationOptions that should be in effect for the system when this application is the active application.  Only certain combinations of NSApplicationPresentationOptions flags are allowed, as detailed in the AppKit Release Notes and the reference documentation for -setPresentationOptions:.  When given an invalid combination of option flags, -setPresentationOptions: raises an exception.
 */
//@property NSApplicationPresentationOptions presentationOptions NS_AVAILABLE_MAC(10_6);

/* Returns the set of application presentation options that are currently in effect for the system.  These are the presentation options that have been put into effect by the currently active application.
 */
//@property (readonly) NSApplicationPresentationOptions currentSystemPresentationOptions NS_AVAILABLE_MAC(10_6);

//@property (readonly) NSApplicationOcclusionState occlusionState NS_AVAILABLE_MAC(10_9);

@end

@interface NSApplication(NSWindowsMenu)
@property (nullable, strong) NSMenu *windowsMenu;
- (void)arrangeInFront:(nullable id)sender;
- (void)removeWindowsItem:(NSWindow *)win;
- (void)addWindowsItem:(NSWindow *)win title:(NSString *)aString filename:(BOOL)isFilename;
- (void)changeWindowsItem:(NSWindow *)win title:(NSString *)aString filename:(BOOL)isFilename;
- (void)updateWindowsItem:(NSWindow *)win;
- (void)miniaturizeAll:(nullable id)sender;
@end

@interface NSApplication(NSFullKeyboardAccess)
/* Use this method to get the status of Full Keyboard Access, as configured in the Keyboard preference pane. You may use this status to implement your own key loop or to implement in-control tabbing behavior similar to NSTableView. Because of the nature of the preference storage, you will not be notified of changes to the key if you attempt to observe it via key-value observing; however, calling this method is fairly inexpensive, so you should always call it when you need the underlying value instead of caching it.
 */
@property (getter=isFullKeyboardAccessEnabled, readonly) BOOL fullKeyboardAccessEnabled NS_AVAILABLE_MAC(10_6);
@end

// return values for -applicationShouldTerminate:
typedef NS_ENUM(NSUInteger, NSApplicationTerminateReply) {
    NSTerminateCancel = 0,
    NSTerminateNow = 1,
    NSTerminateLater = 2
};

// return values for -application:printFiles:withSettings:showPrintPanels:.
typedef NS_ENUM(NSUInteger, NSApplicationPrintReply) {
    NSPrintingCancelled = 0,
    NSPrintingSuccess = 1,
    NSPrintingFailure = 3,
    NSPrintingReplyLater = 2
};

@protocol NSApplicationDelegate <NSObject>
@optional
/*
 Allowable return values are:
 NSTerminateNow - it is ok to proceed with termination
 NSTerminateCancel - the application should not be terminated
 NSTerminateLater - it may be ok to proceed with termination later.  The application must call -replyToApplicationShouldTerminate: with YES or NO once the answer is known
 this return value is for delegates who need to provide document modal alerts (sheets) in order to decide whether to quit.
 */
- (NSApplicationTerminateReply)applicationShouldTerminate:(NSApplication *)sender;
- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename;
- (void)application:(NSApplication *)sender openFiles:(NSArray<NSString *> *)filenames;
- (BOOL)application:(NSApplication *)sender openTempFile:(NSString *)filename;
- (BOOL)applicationShouldOpenUntitledFile:(NSApplication *)sender;
- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender;
- (BOOL)application:(id)sender openFileWithoutUI:(NSString *)filename;
- (BOOL)application:(NSApplication *)sender printFile:(NSString *)filename;
- (NSApplicationPrintReply)application:(NSApplication *)application printFiles:(NSArray<NSString *> *)fileNames withSettings:(NSDictionary<NSString *, id> *)printSettings showPrintPanels:(BOOL)showPrintPanels;
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender;
- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag;
- (nullable NSMenu *)applicationDockMenu:(NSApplication *)sender;
- (NSError *)application:(NSApplication *)application willPresentError:(NSError *)error;

- (void)application:(NSApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken NS_AVAILABLE_MAC(10_7);
- (void)application:(NSApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error NS_AVAILABLE_MAC(10_7);
- (void)application:(NSApplication *)application didReceiveRemoteNotification:(NSDictionary<NSString *, id> *)userInfo NS_AVAILABLE_MAC(10_7);

/* Method called by -[NSApplication encodeRestorableStateWithCoder:] to give the delegate a chance to encode any additional state into the NSCoder. If the restorable state managed by the delegate changes, you must call -[NSApplication invalidateRestorableState] so that it will be re-encoded. See the header NSWindowRestoration.h for more information.
 */
- (void)application:(NSApplication *)app willEncodeRestorableState:(NSCoder *)coder NS_AVAILABLE_MAC(10_7);

/* Method called by -[NSApplication restoreStateWithCoder:] to give the delegate a chance to restore its own state, which it may decode from the NSCoder. See the header NSWindowRestoration.h for more information.
 */
- (void)application:(NSApplication *)app didDecodeRestorableState:(NSCoder *)coder NS_AVAILABLE_MAC(10_7);

/* NSUserActivity support:
 */

/*
 
 This will be called on the main thread as soon as the user indicates they want to continue an activity in your application. The NSUserActivity object may not be available instantly, so use this as an opportunity to show the user that an activity will be continued shortly. Return YES to indicate that you are doing so. Return NO (or leave it unimplemented) and AppKit/UIKit will put up a default UI.
 
 For each application:willContinueUserActivityWithType: invocation, you are guaranteed to get exactly one invocation of application:continueUserActivity:restorationHandler: on success, or application:didFailToContinueUserActivityWithType:error: if an error was encountered.
 */
- (BOOL)application:(NSApplication *)application willContinueUserActivityWithType:(NSString *)userActivityType NS_AVAILABLE_MAC(10_10);

/*
 This will be called on the main thread after the NSUserActivity object is available. Use the data you stored in the NSUserActivity object to re-create what the user was doing. Return YES to indicate that the activity was handled. Return NO (or leave it unimplemented) and AppKit will attempt to continue the user activity.
 
 You should create/fetch any restorable objects associated with the user activity, and pass them to the restorationHandler. They will then get the above restoreUserActivityState: method invoked with the user activity. Invoking the restorationHandler is optional. It may be copied and invoked later, but must be invoked on the main thread.
 
 If this user activity was created automatically by having NSUbiquitousDocumentUserActivityType in a CFBundleDocumentTypes entry, AppKit can automatically restore the NSUserActivity on OS X if NO is returned, or this method is unimplemented. It will do so by creating a document of the appropriate type using the URL stored in the userInfo under the NSUserActivityDocumentURLKey. The document will have restoreUserActivity: called on it.
 */
- (BOOL)application:(NSApplication *)application continueUserActivity:(NSUserActivity *)userActivity restorationHandler:(void(^)(NSArray *restorableObjects))restorationHandler NS_AVAILABLE_MAC(10_10);

/* There are instances where continuing a NSUserActivity may fail. This will get called on the main thread if it does so. If it is unimplemented, AppKit will present the error. */
- (void)application:(NSApplication *)application didFailToContinueUserActivityWithType:(NSString *)userActivityType error:(NSError *)error NS_AVAILABLE_MAC(10_10);

/* This will be called on the main thread when a user activity managed by AppKit/UIKit has been updated. You should use this as a last chance to add additional data to the userActivity. */
- (void)application:(NSApplication *)application didUpdateUserActivity:(NSUserActivity *)userActivity NS_AVAILABLE_MAC(10_10);

/* Notifications:
 */
- (void)applicationWillFinishLaunching:(NSNotification *)notification;
- (void)applicationDidFinishLaunching:(NSNotification *)notification;
- (void)applicationWillHide:(NSNotification *)notification;
- (void)applicationDidHide:(NSNotification *)notification;
- (void)applicationWillUnhide:(NSNotification *)notification;
- (void)applicationDidUnhide:(NSNotification *)notification;
- (void)applicationWillBecomeActive:(NSNotification *)notification;
- (void)applicationDidBecomeActive:(NSNotification *)notification;
- (void)applicationWillResignActive:(NSNotification *)notification;
- (void)applicationDidResignActive:(NSNotification *)notification;
- (void)applicationWillUpdate:(NSNotification *)notification;
- (void)applicationDidUpdate:(NSNotification *)notification;
- (void)applicationWillTerminate:(NSNotification *)notification;
- (void)applicationDidChangeScreenParameters:(NSNotification *)notification;
- (void)applicationDidChangeOcclusionState:(NSNotification *)notification NS_AVAILABLE_MAC(10_9);

@end

@interface NSApplication(NSServicesMenu)
@property (nullable, strong) NSMenu *servicesMenu;
- (void)registerServicesMenuSendTypes:(NSArray<NSString *> *)sendTypes returnTypes:(NSArray<NSString *> *)returnTypes;
@end

@protocol NSServicesMenuRequestor <NSObject>
@optional
//- (BOOL)writeSelectionToPasteboard:(NSPasteboard *)pboard types:(NSArray<NSString *> *)types;
//- (BOOL)readSelectionFromPasteboard:(NSPasteboard *)pboard;
@end

@interface NSApplication(NSServicesHandling)
@property (nullable, strong) id servicesProvider;
@end

@interface NSApplication(NSStandardAboutPanel)
- (void)orderFrontStandardAboutPanel:(nullable id)sender;
- (void)orderFrontStandardAboutPanelWithOptions:(NSDictionary<NSString *, id> *)optionsDictionary;


/* Optional keys in optionsDictionary:
 
 @"Credits": NSAttributedString displayed in the info area of the panel. If
 not specified, contents obtained from "Credits.rtf" in [NSBundle mainBundle];
 if not available, blank.
 
 @"ApplicationName": NSString displayed in place of the default app name. If
 not specified, uses the value of CFBundleName (localizable). Fallback is [[NSProcessInfo processInfo] processName].
 
 @"ApplicationIcon": NSImage displayed in place of NSApplicationIcon. If not
 specified, use [NSImage imageNamed:@"NSApplicationIcon"]; if not available, generic icon.
 
 @"Copyright": NSString containing the copyright string. If not specified,
 obtain from the value of NSHumanReadableCopyright (localizable) in infoDictionary; if not available, leave blank.
 
 @"Version": NSString containing the build version number of the application
 ("58.4", "1.2d3"); displayed as "Version 58.4" or "Version 1.0 (58.4) depending on the presence of ApplicationVersion.
 If not specified, obtain from the CFBundleVersion key in infoDictionary; if not specified or empty string, leave blank.
 
 @"ApplicationVersion": NSString displayed as the marketing version  ("1.0", "Mac OS X", "3", "WebObjects 3.5", ...), before the build version.
 If not specified, obtain from CFBundleShortVersionString key in infoDictionary. Prefixed with word "Version" if it looks like a number.
 */

@end

/* Bi-directional User Interface
 */

@interface NSApplication (NSApplicationLayoutDirection)
//property (readonly) NSUserInterfaceLayoutDirection userInterfaceLayoutDirection NS_AVAILABLE_MAC(10_6); // Returns the application-wide user interface layout direction.
@end

@interface NSApplication (NSRestorableUserInterface)

/* Disable or reenable relaunching this app on login, if the app was running at the time the user logged out.  These methods increment and decrement a counter respectively; if the counter is 0 at the time the user logs out, then the app may be relaunched when the user logs back in.  The counter is initially zero, so by default apps are relaunched.
 
 If your app should not be relaunched because it launches via some other mechanism (e.g. launchd), then the recommended usage is to call [NSApp disableRelaunchOnLogin] once, and never pair it with an -enable call.
 
 If your app should not be relaunched because it triggers a restart (e.g. an installer), then the recommended usage is to call [NSApp disableRelaunchOnLogin] immediately before you attempt to trigger a restart, and [NSApp enableRelaunchOnLogin] immediately after.  This is because the user may cancel restarting; if the user later restarts for another reason, then your app should be brought back.
 
 These methods are thread safe.
 */
- (void)disableRelaunchOnLogin NS_AVAILABLE_MAC(10_7);
- (void)enableRelaunchOnLogin NS_AVAILABLE_MAC(10_7);
@end

typedef NS_OPTIONS(NSUInteger, NSRemoteNotificationType) {
    NSRemoteNotificationTypeNone NS_ENUM_AVAILABLE_MAC(10_7)    = 0,
    NSRemoteNotificationTypeBadge NS_ENUM_AVAILABLE_MAC(10_7)   = 1 << 0,
    NSRemoteNotificationTypeSound NS_ENUM_AVAILABLE_MAC(10_8)   = 1 << 1,
    NSRemoteNotificationTypeAlert NS_ENUM_AVAILABLE_MAC(10_8)   = 1 << 2,
};


@interface NSApplication (NSRemoteNotifications)
- (void)registerForRemoteNotificationTypes:(NSRemoteNotificationType)types NS_AVAILABLE_MAC(10_7);
- (void)unregisterForRemoteNotifications NS_AVAILABLE_MAC(10_7);

@property (readonly) NSRemoteNotificationType enabledRemoteNotificationTypes NS_AVAILABLE_MAC(10_7);
@end

/* An Application's startup function */

//UIKIT_EXTERN int UIApplicationMain(int argc, const char *argv[]);

/* NSApplicationLoad should be called when loading a Cocoa bundle in a Carbon app in order to initialize NSApplication and other Cocoa objects.  Redundant calls are ignored.
 */
UIKIT_EXTERN BOOL NSApplicationLoad(void);

/* NSShowsServicesMenuItem() always returns YES. */
UIKIT_EXTERN BOOL NSShowsServicesMenuItem(NSString *itemName);

/* NSSetShowsServicesMenuItem() has no effect, and always returns 0. */
UIKIT_EXTERN NSInteger NSSetShowsServicesMenuItem(NSString *itemName, BOOL enabled);

/* NSUpdateDynamicServices() causes the services information for the system to be updated.  This will only be necessary if your program adds dynamic services to the system (i.e. services not found in mach-o segments of executables).
 */
UIKIT_EXTERN void NSUpdateDynamicServices(void);
//UIKIT_EXTERN BOOL NSPerformService(NSString *itemName, NSPasteboard * __nullable pboard);

UIKIT_EXTERN void NSRegisterServicesProvider(id __nullable provider, NSString *name); // apps should use -setServicesProvider
UIKIT_EXTERN void NSUnregisterServicesProvider(NSString *name);

/* Notifications */


/* User info keys for NSApplicationDidFinishLaunchingNotification */

/* The following key is present in the userInfo of NSApplicationDidFinishLaunchingNotification.  Its value is an NSNumber containing a bool.  It will be NO if the app was launched to open or print a file, to perform a Service, if the app had saved state that will be restored, or if the app launch was in some other sense not a "default" launch.  Otherwise its value will be YES.
 */
UIKIT_EXTERN NSString * const NSApplicationLaunchIsDefaultLaunchKey NS_AVAILABLE_MAC(10_7);

/* The following key is present in the userInfo of NSApplicationDidFinishLaunchingNotification. It will be present if your application was launched because a user activated a notification in the Notification Center. Its value is an NSUserNotification object. */
UIKIT_EXTERN NSString * const NSApplicationLaunchUserNotificationKey NS_AVAILABLE_MAC(10_8);

/* Deprecated Keys for NSApplicationDidFinishLaunchingNotification */
/* NSApplicationLaunchRemoteNotificationKey is unimplemented.  Please use NSApplicationLaunchUserNotificationKey to get the NSUserNotification object.  The NSUserNotification object has an isRemote property to indicate whether this application was launched as a result of a remote notification */
UIKIT_EXTERN NSString * const NSApplicationLaunchRemoteNotificationKey NS_DEPRECATED_MAC(10_7, 10_8);

/* Upon receiving this notification, you can query the NSApplication for its occlusion state. Note that this only notifies about changes in the state of the occlusion, not when the occlusion region changes. You can use this notification to increase responsiveness and save power, by halting any expensive calculations that the user can not see. */
UIKIT_EXTERN NSString * const NSApplicationDidChangeOcclusionStateNotification NS_AVAILABLE_MAC(10_9);


/* Deprecated Methods */
@interface NSApplication (NSDeprecated)

/*
 ** runModalForWindow:relativeToWindow: was deprecated in Mac OS 10.0.
 ** Please use -[NSWindow beginSheet:completionHandler:] instead
 */
- (NSInteger)runModalForWindow:(null_unspecified NSWindow *)theWindow relativeToWindow:(null_unspecified NSWindow *)docWindow NS_DEPRECATED_MAC(10_0, 10_0);

/*
 ** beginModalSessionForWindow:relativeToWindow: was deprecated in Mac OS 10.0.
 ** Please use -[NSWindow beginSheet:completionHandler:] instead
 */
//- (NSModalSession)beginModalSessionForWindow:(null_unspecified NSWindow *)theWindow relativeToWindow:(null_unspecified NSWindow *)docWindow NS_RETURNS_INNER_POINTER NS_DEPRECATED_MAC(10_0, 10_0);

// -application:printFiles: was deprecated in Mac OS 10.4. Implement application:printFiles:withSettings:showPrintPanels: in your application delegate instead.
- (void)application:(null_unspecified NSApplication *)sender printFiles:(null_unspecified NSArray<NSString *> *)filenames NS_DEPRECATED_MAC(10_3, 10_4);

/* These constants are deprecated in 10.9 and will be formally deprecated in the following release */
enum {
    NSRunStoppedResponse NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSModalResponseStop instead") = (-1000),
    NSRunAbortedResponse NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSModalResponseAbort instead") = (-1001),
    NSRunContinuesResponse NS_ENUM_DEPRECATED_MAC(10_0, 10_10, "Use NSModalResponseContinue instead") = (-1002)
};

/* These methods are deprecated in 10.9 and will be formally deprecated in the following release.
 NSWindow's -beginSheet:completionHandler: and -endSheet:returnCode: should be used instead.
 NSApplication's -beginSheet:modalForWindow:modalDelegate:didEndSelector:contextInfo: will continue to work as it previously did, leaking contextInfo and failing when there is already an existing sheet.
 */
- (void)beginSheet:(NSWindow *)sheet modalForWindow:(NSWindow *)docWindow modalDelegate:(nullable id)modalDelegate didEndSelector:(nullable SEL)didEndSelector contextInfo:(null_unspecified void *)contextInfo NS_DEPRECATED_MAC(10_0, 10_10, "Use -[NSWindow beginSheet:completionHandler:] instead");
- (void)endSheet:(NSWindow *)sheet NS_DEPRECATED_MAC(10_0, 10_10, "Use -[NSWindow endSheet:] instead");
- (void)endSheet:(NSWindow *)sheet returnCode:(NSInteger)returnCode NS_DEPRECATED_MAC(10_0, 10_10, "Use -[NSWindow endSheet:returnCode:] instead");


@end

//UI_ASSUME_NONNULL_END


