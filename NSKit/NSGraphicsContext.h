//
//  NSGraphicsContext.h
//  NSKit
//
//  Created by Sterling  on 11/10/2016.
//  Copyright © 2016 TheHitherGuy. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
typedef CGPoint NSPoint;
@interface NSGraphicsContext : NSObject
+ (nullable NSGraphicsContext *)graphicsContextWithAttributes:(NSDictionary<NSString *, id> *)attributes;

// Convenience cover method for [NSGraphicsContext graphicsContextWithAttributes:[NSDictionary dictionaryWithObject:<NSWindow instance> forKey:NSGraphicsContextDestinationAttributeName]]
+ (NSGraphicsContext *)graphicsContextWithWindow:(NSWindow *)window;

/* Convenience cover method for [NSGraphicsContext graphicsContextWithAttributes:[NSDictionary dictionaryWithObject:<NSBitmapImageRep instance> forKey:NSGraphicsContextDestinationAttributeName]]. Only NSBitmapImageRep instances with isPlanar == NO are supported.
 */
//+ (nullable NSGraphicsContext *)graphicsContextWithBitmapImageRep:(UIBitmapImageRep *)bitmapRep;

/* Instantiates from a CGContextRef.  initialFlippedState is used to determine the return value from -isFlipped when no view is focused in the context.
 */
+ (NSGraphicsContext *)graphicsContextWithCGContext:(CGContextRef)graphicsPort flipped:(BOOL)initialFlippedState NS_AVAILABLE_MAC(10_10);

// Setting and identifying the current context in the thread
+ (nullable NSGraphicsContext *)currentContext;
+ (void)setCurrentContext:(nullable NSGraphicsContext *)context;

// Convenience cover method for [[NSGraphicsContext currentContext] isDrawingToScreen]
+ (BOOL)currentContextDrawingToScreen;

// Graphics state controls
// Calls -saveGraphicsContext, and pushes the current context on per-thread stack. It's functional equivalent of PSgsave
+ (void)saveGraphicsState;
// Pops a context from per-thread stack, makes it current, and calls -restoreGraphicsContext. It's functional equivalent of PSgrestore
+ (void)restoreGraphicsState;

// Returns attributes used to create this instance
@property (nullable, readonly, copy) NSDictionary<NSString *, id> *attributes;

// Testing the drawing destination
@property (getter=isDrawingToScreen, readonly) BOOL drawingToScreen;

// Controlling the context
- (void)saveGraphicsState;
- (void)restoreGraphicsState;

- (void)flushGraphics;

@property (readonly) CGContextRef CGContext NS_RETURNS_INNER_POINTER NS_AVAILABLE_MAC(10_10);

/* Returns the flip state of the receiver.  The state is determined by messaging -isFlipped to the focus view in the context.  If no view has focus, returns NO unless the receiver is instantiated via graphicsContextWithGraphicsPort:drawingToScreen:flipped: with initialFlippedState == YES.
 */
@property (getter=isFlipped, readonly) BOOL flipped;
@end

@interface NSGraphicsContext(NSGraphicsContext_RenderingOptions)

@property BOOL shouldAntialias;
//@property NSImageInterpolation imageInterpolation;

@property NSPoint patternPhase;
//property NSCompositingOperation compositingOperation;
//@property NSColorRenderingIntent colorRenderingIntent NS_AVAILABLE_MAC(10_5);
@end

@class CIContext;
@interface NSGraphicsContext (NSQuartzCoreAdditions)
@property (nullable, readonly, strong) CIContext *CIContext;
@end

@interface NSGraphicsContext (NSGraphicsContextDeprecated)

/* This method does nothing and is deprecated
 */
+ (void)setGraphicsState:(NSInteger)gState NS_DEPRECATED_MAC(10_0, 10_10);

- (null_unspecified id)focusStack NS_DEPRECATED_MAC(10_0, 10_6);
- (void)setFocusStack:(null_unspecified id)stack NS_DEPRECATED_MAC(10_0, 10_6);

// Platform specific graphics ports (usually CGContextRef.) Use +graphicsContextWithCGContext:flipped: and -CGContext instead.
+ (NSGraphicsContext *)graphicsContextWithGraphicsPort:(void *)graphicsPort flipped:(BOOL)initialFlippedState;
@property (readonly) void *graphicsPort NS_RETURNS_INNER_POINTER;

@end


