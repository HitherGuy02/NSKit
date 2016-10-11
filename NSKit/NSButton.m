//
//  NSButton.m
//  NSKit
//
//  Created by Sterling  on 11/10/2016.
//  Copyright © 2016 TheHitherGuy. All rights reserved.
//

#import "NSButton.h"

@implementation NSButton

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/
-(NSString*)title {
    return [self titleForState:UIControlStateNormal];
}
@end
