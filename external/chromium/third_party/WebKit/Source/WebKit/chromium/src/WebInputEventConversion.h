/*
 * Copyright (C) 2009 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WebInputEventConversion_h
#define WebInputEventConversion_h

#include "PlatformGestureEvent.h"
#include "PlatformKeyboardEvent.h"
#include "PlatformMouseEvent.h"
#include "PlatformTouchEvent.h"
#include "PlatformWheelEvent.h"
#include "WebInputEvent.h"

namespace WebCore {
class GestureEvent;
class KeyboardEvent;
class MouseEvent;
class RenderObject;
class ScrollView;
class TouchEvent;
class WheelEvent;
class Widget;
}

namespace WebKit {

class WebMouseEvent;
class WebMouseWheelEvent;
class WebKeyboardEvent;
class WebTouchEvent;
class WebGestureEvent;

// These classes are used to convert from WebInputEvent subclasses to
// corresponding WebCore events.

class PlatformMouseEventBuilder : public WebCore::PlatformMouseEvent {
public:
    PlatformMouseEventBuilder(WebCore::Widget*, const WebMouseEvent&);
};

class PlatformWheelEventBuilder : public WebCore::PlatformWheelEvent {
public:
    PlatformWheelEventBuilder(WebCore::Widget*, const WebMouseWheelEvent&);
};

#if ENABLE(GESTURE_EVENTS)
class PlatformGestureEventBuilder : public WebCore::PlatformGestureEvent {
public:
    PlatformGestureEventBuilder(WebCore::Widget*, const WebGestureEvent&);
};
#endif

class PlatformKeyboardEventBuilder : public WebCore::PlatformKeyboardEvent {
public:
    PlatformKeyboardEventBuilder(const WebKeyboardEvent&);
    void setKeyType(Type);
    bool isCharacterKey() const;
};

#if ENABLE(TOUCH_EVENTS)
// Converts a WebTouchPoint to a WebCore::PlatformTouchPoint.
class PlatformTouchPointBuilder : public WebCore::PlatformTouchPoint {
public:
    PlatformTouchPointBuilder(WebCore::Widget*, const WebTouchPoint&);
};

// Converts a WebTouchEvent to a WebCore::PlatformTouchEvent.
class PlatformTouchEventBuilder : public WebCore::PlatformTouchEvent {
public:
    PlatformTouchEventBuilder(WebCore::Widget*, const WebTouchEvent&);
};
#endif

// Converts a WebCore::MouseEvent to a corresponding WebMouseEvent.
// NOTE: This is only implemented for mousemove, mouseover, mouseout,
// mousedown and mouseup.  If the event mapping fails, the event type will
// be set to Undefined.
class WebMouseEventBuilder : public WebMouseEvent {
public:
    WebMouseEventBuilder(const WebCore::Widget*, const WebCore::RenderObject*, const WebCore::MouseEvent&);
#if ENABLE(TOUCH_EVENTS)
    WebMouseEventBuilder(const WebCore::Widget*, const WebCore::RenderObject*, const WebCore::TouchEvent&);
#endif
};

// Converts a WebCore::WheelEvent to a corresponding WebMouseWheelEvent.
// If the event mapping fails, the event type will be set to Undefined.
class WebMouseWheelEventBuilder : public WebMouseWheelEvent {
public:
    WebMouseWheelEventBuilder(const WebCore::Widget*, const WebCore::RenderObject*, const WebCore::WheelEvent&);
};

// Converts a WebCore::KeyboardEvent to a corresponding WebKeyboardEvent.
// NOTE: This is only implemented for keydown and keyup.  If the event mapping
// fails, the event type will be set to Undefined.
class WebKeyboardEventBuilder : public WebKeyboardEvent {
public:
    WebKeyboardEventBuilder(const WebCore::KeyboardEvent&);
};

#if ENABLE(TOUCH_EVENTS)
// Converts a WebCore::TouchEvent to a corresponding WebTouchEvent.
// NOTE: WebTouchEvents have a cap on the number of WebTouchPoints. Any points
// exceeding that cap will be dropped.
class WebTouchEventBuilder : public WebTouchEvent {
public:
    WebTouchEventBuilder(const WebCore::Widget*, const WebCore::RenderObject*, const WebCore::TouchEvent&);
};
#endif // ENABLE(TOUCH_EVENTS)

#if ENABLE(GESTURE_EVENTS)
// Converts WebCore::GestureEvent to a corresponding WebGestureEvent.
// NOTE: If event mapping fails, the type will be set to Undefined.
class WebGestureEventBuilder : public WebGestureEvent {
public:
    WebGestureEventBuilder(const WebCore::Widget*, const WebCore::RenderObject*, const WebCore::GestureEvent&);
};
#endif // ENABLE(GESTURE_EVENTS)

} // namespace WebKit

#endif