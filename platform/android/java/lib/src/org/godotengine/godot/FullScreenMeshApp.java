/*************************************************************************/
/*  FullScreenMeshApp.java                                              */
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

import android.content.ComponentName;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import androidx.annotation.CallSuper;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;

/**
 * Base activity for Android apps intending to use Mesh as the primary and only screen.
 *
 * It's also a reference implementation for how to setup and use the {@link Mesh} fragment
 * within an Android app.
 */
public abstract class FullScreenMeshApp extends FragmentActivity implements MeshHost {
	private static final String TAG = FullScreenMeshApp.class.getSimpleName();

	@Nullable
	private Mesh meshFragment;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.mesh_app_layout);

		Fragment currentFragment = getSupportFragmentManager().findFragmentById(R.id.mesh_fragment_container);
		if (currentFragment instanceof Mesh) {
			Log.v(TAG, "Reusing existing Mesh fragment instance.");
			meshFragment = (Mesh)currentFragment;
		} else {
			Log.v(TAG, "Creating new Mesh fragment instance.");
			meshFragment = initMeshInstance();
			if (meshFragment == null) {
				throw new IllegalStateException("Mesh instance must be non-null.");
			}

			getSupportFragmentManager().beginTransaction().replace(R.id.mesh_fragment_container, meshFragment).setPrimaryNavigationFragment(meshFragment).commitNowAllowingStateLoss();
		}
	}

	@Override
	public void onDestroy() {
		super.onDestroy();
		onMeshForceQuit(meshFragment);
	}

	@Override
	public final void onMeshForceQuit(Mesh instance) {
		if (instance == meshFragment) {
			System.exit(0);
		}
	}

	@Override
	public final void onMeshRestartRequested(Mesh instance) {
		if (instance == meshFragment) {
			// HACK:
			//
			// Currently it's very hard to properly deinitialize Mesh on Android to restart the game
			// from scratch. Therefore, we need to kill the whole app process and relaunch it.
			//
			// Restarting only the activity, wouldn't be enough unless it did proper cleanup (including
			// releasing and reloading native libs or resetting their state somehow and clearing statics).
			//
			// Using instrumentation is a way of making the whole app process restart, because Android
			// will kill any process of the same package which was already running.
			//
			Bundle args = new Bundle();
			args.putParcelable("intent", getIntent());
			startInstrumentation(new ComponentName(this, MeshInstrumentation.class), null, args);
		}
	}

	@Override
	public void onNewIntent(Intent intent) {
		super.onNewIntent(intent);
		if (meshFragment != null) {
			meshFragment.onNewIntent(intent);
		}
	}

	@CallSuper
	@Override
	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		if (meshFragment != null) {
			meshFragment.onActivityResult(requestCode, resultCode, data);
		}
	}

	@CallSuper
	@Override
	public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
		super.onRequestPermissionsResult(requestCode, permissions, grantResults);
		if (meshFragment != null) {
			meshFragment.onRequestPermissionsResult(requestCode, permissions, grantResults);
		}
	}

	@Override
	public void onBackPressed() {
		if (meshFragment != null) {
			meshFragment.onBackPressed();
		} else {
			super.onBackPressed();
		}
	}

	/**
	 * Used to initialize the Mesh fragment instance in {@link FullScreenMeshApp#onCreate(Bundle)}.
	 */
	@NonNull
	protected Mesh initMeshInstance() {
		return new Mesh();
	}

	@Nullable
	protected final Mesh getMeshFragment() {
		return meshFragment;
	}
}
