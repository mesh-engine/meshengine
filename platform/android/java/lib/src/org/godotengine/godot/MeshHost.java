/*************************************************************************/
/*  MeshHost.java                                                       */
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

package org.meshengine.mesh;

import java.util.Collections;
import java.util.List;

/**
 * Denotate a component (e.g: Activity, Fragment) that hosts the {@link Mesh} fragment.
 */
public interface MeshHost {
	/**
	 * Provides a set of command line parameters to setup the engine.
	 */
	default List<String> getCommandLine() {
		return Collections.emptyList();
	}

	/**
	 * Invoked on the render thread when the Mesh setup is complete.
	 */
	default void onMeshSetupCompleted() {}

	/**
	 * Invoked on the render thread when the Mesh main loop has started.
	 */
	default void onMeshMainLoopStarted() {}

	/**
	 * Invoked on the UI thread as the last step of the Mesh instance clean up phase.
	 */
	default void onMeshForceQuit(Mesh instance) {}

	/**
	 * Invoked on the GL thread when the Mesh instance wants to be restarted. It's up to the host
	 * to perform the appropriate action(s).
	 */
	default void onMeshRestartRequested(Mesh instance) {}
}
