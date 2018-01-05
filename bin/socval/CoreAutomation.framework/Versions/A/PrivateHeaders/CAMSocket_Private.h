//
//  CAMSocket_Private.h
//  CoreAutomation
//
//  Created by Chen Huang on 9/25/15.
//
//

#ifndef CAMSocket_Private_h
#define CAMSocket_Private_h

typedef void(^EventHandler)(void);

@interface CAMSocket()
{
    dispatch_queue_t    qSocketIO;
    dispatch_source_t   socketReadSource;
    NSCondition         *socketSourceCond;
    bool                isBroken;
}
@property (assign, readwrite) BOOL isConnectionStarted;
@property (copy, readwrite) EventHandler readEventHandler;
@property (copy, readwrite) EventHandler cancelEventHandler;

- (unsigned long)bytesAvailableToRead;
- (void)dispatcherStopped;

@end

#endif /* CAMSocket_Private_h */
