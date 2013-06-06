//
//  ViewController.m
//  AntiReplayIOS
//
//  Created by Kris Meeusen on 13/02/13.
//  Copyright (c) 2013 Kris Meeusen. All rights reserved.
//

#import "ViewController.h"
#import "mainController.h"

#import "TouchDispatcher.h"
#import "App.h"

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
    
    gl2::App::Instance()->screenSize = screenSize;


    

    
    UIInterfaceOrientation orientation = [[UIApplication sharedApplication] statusBarOrientation];
    [self updateOrientation:orientation];
    
    [[NSNotificationCenter defaultCenter]
     addObserver:self
     selector:@selector(deviceOrientationDidChangeNotification:)
     name:UIApplicationDidChangeStatusBarOrientationNotification
     object:nil];

}


- (std::vector<ci::Vec2f>) NSSetToVector:(NSObject <NSFastEnumeration>*) set{
    
    std::vector<ci::Vec2f> touchVec;

	for(UITouch* touch in set) {
        CGPoint touchPoint = [touch locationInView:self.view];
        touchVec.push_back(ci::Vec2f(touchPoint.x,screenSize.y - touchPoint.y));
	}
    
    return touchVec;   
}


- (void)deviceOrientationDidChangeNotification:(NSNotification*)notification
{
    
//    UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
    UIInterfaceOrientation orientation = [[UIApplication sharedApplication] statusBarOrientation];
    [self updateOrientation:orientation];
}


-(void) updateOrientation: (UIInterfaceOrientation) orientation
{
  //  NSLog("%@",orientation);
    std::cout << orientation << std::endl;
    switch (orientation)
    {
            
        case UIInterfaceOrientationPortrait:
            gl2::App::Instance()->orientationChanged(gl2::Portrait);
            std::cout << "portrait" << std::endl;
            break;
        case UIInterfaceOrientationPortraitUpsideDown:
            gl2::App::Instance()->orientationChanged(gl2::PortraitUpsideDown);
            std::cout << "portrait" << std::endl;
            break;
        case UIInterfaceOrientationLandscapeLeft:
            gl2::App::Instance()->orientationChanged(gl2::LandscapeLeft);
            std::cout << "landscape" << std::endl;
            break;
            
        case UIInterfaceOrientationLandscapeRight:
            gl2::App::Instance()->orientationChanged(gl2::LandscapeRight);
            std::cout << "landscape" << std::endl;

            break;
    }

}



- (void) updateTouches{
	
	//std::cout << "touch points send " << touchVec.size() << std::endl;
    TouchDispatcher::Instance()->setActiveTouches([self NSSetToVector:activeTouches]);
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {

	for(UITouch* touch in touches) {
        [activeTouches addObject:touch];
	}
        
    TouchDispatcher::Instance()->touchesBegan([self NSSetToVector:touches]);
	std::cout << "#began #" << std::endl;

	[self updateTouches];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {

    TouchDispatcher::Instance()->touchesMoved([self NSSetToVector:touches]);
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
    
    
    TouchDispatcher::Instance()->touchesEnded([self NSSetToVector:touches]);
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
