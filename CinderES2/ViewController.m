//
//  ViewController.m
//  AntiReplayIOS
//
//  Created by Kris Meeusen on 13/02/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//

#import "ViewController.h"
#import "mainController.h"

#include <vector>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))


@interface ViewController () {
	mainController main;
	GLKView *view;
	
	ci::Vec2f screenSize;

	NSMutableArray* activeTouches;
}

@property (strong, nonatomic) EAGLContext *context;

- (void)setupGL;
- (void)tearDownGL;

@end

@implementation ViewController

- (void)dealloc
{
    [self tearDownGL];
    
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
    
    [_context release];
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2] autorelease];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }

    view = (GLKView *)self.view;
	view.contentScaleFactor = [[UIScreen mainScreen] scale];

	self.preferredFramesPerSecond = 60;

	view.multipleTouchEnabled =  true;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat16;
	activeTouches = [[NSMutableArray alloc] init];
	
	std::cout << [[UIScreen mainScreen] scale] << std::endl;
	
    [self setupGL];
    
	view.backgroundColor = [UIColor blackColor];
//	view. = [NSDictionary dictionaryWithObjectsAndKeys:
//                                    [NSNumber numberWithBool:YES], kEAGLDrawablePropertyRetainedBacking, kEAGLColorFormatRGBA8, kEAGLDrawablePropertyColorFormat, nil];
    main.setup();
	screenSize.set(CGRectGetWidth([UIScreen mainScreen].applicationFrame),CGRectGetHeight([UIScreen mainScreen].applicationFrame));
	main.setSize(screenSize);

}


- (void) updateTouches{
	
	std::vector<ci::Vec2f> touchVec;
	for (int i=0; i < [activeTouches count]; ++i) {
			CGPoint touchPoint = [activeTouches[i] locationInView:self.view];
			touchVec.push_back(ci::Vec2f(touchPoint.x,screenSize.y - touchPoint.y));
	}

	//std::cout << "touch points send " << touchVec.size() << std::endl;

	main.setActiveTouches(touchVec);
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    //self.paused = !self.paused;
	std::vector<ci::Vec2f> touchVec;

	for(UITouch* touch in touches) {
		[activeTouches addObject:touch];

	}

	[self updateTouches];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {

	[self updateTouches];
}

- (void) touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{

	NSMutableArray *discardedItems = [NSMutableArray array];
	for(UITouch* touch in touches) {
		if ([activeTouches containsObject:touch]) {
			[discardedItems addObject:touch];
		}
	}
	[activeTouches removeObjectsInArray:discardedItems];
	[self updateTouches];

}

- (void) touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event{

	NSMutableArray *discardedItems = [NSMutableArray array];
	for(UITouch* touch in touches) {
		if ([activeTouches containsObject:touch] && touch.phase == UITouchPhaseCancelled) {
			[discardedItems addObject:touch];
		}
	}
	[activeTouches removeObjectsInArray:discardedItems];
	[self updateTouches];

}


- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        [self tearDownGL];
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.context];
    
    glEnable(GL_DEPTH_TEST);
    
 }

- (void)tearDownGL
{
    [EAGLContext setCurrentContext:self.context];
}

#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{
	main.update();

}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
	main.draw();
}

@end
