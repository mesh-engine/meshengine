/*************************************************************************/
/*  MeshGestureHandler.java                                             */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           MESH ENGINE                                */
/*                      https://mesh-engine.com                          */
/*************************************************************************/
/* Copyright (c) 2007-2021 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2021 Mesh Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

package org.meshengine.mesh.input;

import org.meshengine.mesh.MeshLib;
import org.meshengine.mesh.MeshRenderView;

import android.view.GestureDetector;
import android.view.MotionEvent;

/**
 * Handles gesture input related events for the {@link MeshRenderView} view.
 * https://developer.android.com/reference/android/view/GestureDetector.SimpleOnGestureListener
 */
public class MeshGestureHandler extends GestureDetector.SimpleOnGestureListener {
	private final MeshRenderView mRenderView;

	public MeshGestureHandler(MeshRenderView meshView) {
		mRenderView = meshView;
	}

	private void queueEvent(Runnable task) {
		mRenderView.queueOnRenderThread(task);
	}

	@Override
	public boolean onDown(MotionEvent event) {
		super.onDown(event);
		//Log.i("MeshGesture", "onDown");
		return true;
	}

	@Override
	public boolean onSingleTapConfirmed(MotionEvent event) {
		super.onSingleTapConfirmed(event);
		return true;
	}

	@Override
	public void onLongPress(MotionEvent event) {
		//Log.i("MeshGesture", "onLongPress");
	}

	@Override
	public boolean onDoubleTap(MotionEvent event) {
		//Log.i("MeshGesture", "onDoubleTap");
		final int x = Math.round(event.getX());
		final int y = Math.round(event.getY());
		final int buttonMask = event.getButtonState();
		MeshLib.doubleTap(buttonMask, x, y);
		return true;
	}

	@Override
	public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
		//Log.i("MeshGesture", "onScroll");
		final int x = Math.round(distanceX);
		final int y = Math.round(distanceY);
		MeshLib.scroll(x, y);
		return true;
	}

	@Override
	public boolean onFling(MotionEvent event1, MotionEvent event2, float velocityX, float velocityY) {
		//Log.i("MeshGesture", "onFling");
		return true;
	}
}
