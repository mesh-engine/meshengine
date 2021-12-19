/*************************************************************************/
/*  editor_internal_calls.cpp                                            */
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

#include "editor_internal_calls.h"

#ifdef UNIX_ENABLED
#include <unistd.h> // access
#endif

#include "core/os/os.h"
#include "core/version.h"
#include "editor/debugger/editor_debugger_node.h"
#include "editor/editor_node.h"
#include "editor/editor_scale.h"
#include "editor/plugins/script_editor_plugin.h"
#include "main/main.h"

#include "../csharp_script.h"
#include "../glue/cs_glue_version.gen.h"
#include "../meshsharp_dirs.h"
#include "../mono_gd/gd_mono_marshal.h"
#include "../utils/osx_utils.h"
#include "code_completion.h"
#include "meshsharp_export.h"

MonoString *mesh_icall_MeshSharpDirs_ResDataDir() {
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_res_data_dir());
}

MonoString *mesh_icall_MeshSharpDirs_ResMetadataDir() {
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_res_metadata_dir());
}

MonoString *mesh_icall_MeshSharpDirs_ResAssembliesBaseDir() {
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_res_assemblies_base_dir());
}

MonoString *mesh_icall_MeshSharpDirs_ResAssembliesDir() {
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_res_assemblies_dir());
}

MonoString *mesh_icall_MeshSharpDirs_ResConfigDir() {
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_res_config_dir());
}

MonoString *mesh_icall_MeshSharpDirs_ResTempDir() {
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_res_temp_dir());
}

MonoString *mesh_icall_MeshSharpDirs_ResTempAssembliesBaseDir() {
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_res_temp_assemblies_base_dir());
}

MonoString *mesh_icall_MeshSharpDirs_ResTempAssembliesDir() {
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_res_temp_assemblies_dir());
}

MonoString *mesh_icall_MeshSharpDirs_MonoUserDir() {
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_mono_user_dir());
}

MonoString *mesh_icall_MeshSharpDirs_MonoLogsDir() {
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_mono_logs_dir());
}

MonoString *mesh_icall_MeshSharpDirs_MonoSolutionsDir() {
#ifdef TOOLS_ENABLED
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_mono_solutions_dir());
#else
	return nullptr;
#endif
}

MonoString *mesh_icall_MeshSharpDirs_BuildLogsDirs() {
#ifdef TOOLS_ENABLED
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_build_logs_dir());
#else
	return nullptr;
#endif
}

MonoString *mesh_icall_MeshSharpDirs_ProjectSlnPath() {
#ifdef TOOLS_ENABLED
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_project_sln_path());
#else
	return nullptr;
#endif
}

MonoString *mesh_icall_MeshSharpDirs_ProjectCsProjPath() {
#ifdef TOOLS_ENABLED
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_project_csproj_path());
#else
	return nullptr;
#endif
}

MonoString *mesh_icall_MeshSharpDirs_DataEditorToolsDir() {
#ifdef TOOLS_ENABLED
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_data_editor_tools_dir());
#else
	return nullptr;
#endif
}

MonoString *mesh_icall_MeshSharpDirs_DataEditorPrebuiltApiDir() {
#ifdef TOOLS_ENABLED
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_data_editor_prebuilt_api_dir());
#else
	return nullptr;
#endif
}

MonoString *mesh_icall_MeshSharpDirs_DataMonoEtcDir() {
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_data_mono_etc_dir());
}

MonoString *mesh_icall_MeshSharpDirs_DataMonoLibDir() {
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_data_mono_lib_dir());
}

MonoString *mesh_icall_MeshSharpDirs_DataMonoBinDir() {
#ifdef WINDOWS_ENABLED
	return GDMonoMarshal::mono_string_from_mesh(MeshSharpDirs::get_data_mono_bin_dir());
#else
	return nullptr;
#endif
}

void mesh_icall_EditorProgress_Create(MonoString *p_task, MonoString *p_label, int32_t p_amount, MonoBoolean p_can_cancel) {
	String task = GDMonoMarshal::mono_string_to_mesh(p_task);
	String label = GDMonoMarshal::mono_string_to_mesh(p_label);
	EditorNode::progress_add_task(task, label, p_amount, (bool)p_can_cancel);
}

void mesh_icall_EditorProgress_Dispose(MonoString *p_task) {
	String task = GDMonoMarshal::mono_string_to_mesh(p_task);
	EditorNode::progress_end_task(task);
}

MonoBoolean mesh_icall_EditorProgress_Step(MonoString *p_task, MonoString *p_state, int32_t p_step, MonoBoolean p_force_refresh) {
	String task = GDMonoMarshal::mono_string_to_mesh(p_task);
	String state = GDMonoMarshal::mono_string_to_mesh(p_state);
	return EditorNode::progress_task_step(task, state, p_step, (bool)p_force_refresh);
}

uint32_t mesh_icall_ExportPlugin_GetExportedAssemblyDependencies(MonoObject *p_initial_assemblies,
		MonoString *p_build_config, MonoString *p_custom_bcl_dir, MonoObject *r_assembly_dependencies) {
	Dictionary initial_dependencies = GDMonoMarshal::mono_object_to_variant(p_initial_assemblies);
	String build_config = GDMonoMarshal::mono_string_to_mesh(p_build_config);
	String custom_bcl_dir = GDMonoMarshal::mono_string_to_mesh(p_custom_bcl_dir);
	Dictionary assembly_dependencies = GDMonoMarshal::mono_object_to_variant(r_assembly_dependencies);

	return MeshSharpExport::get_exported_assembly_dependencies(initial_dependencies, build_config, custom_bcl_dir, assembly_dependencies);
}

MonoString *mesh_icall_Internal_UpdateApiAssembliesFromPrebuilt(MonoString *p_config) {
	String config = GDMonoMarshal::mono_string_to_mesh(p_config);
	String error_str = GDMono::get_singleton()->update_api_assemblies_from_prebuilt(config);
	return GDMonoMarshal::mono_string_from_mesh(error_str);
}

MonoString *mesh_icall_Internal_FullTemplatesDir() {
	String full_templates_dir = EditorSettings::get_singleton()->get_templates_dir().plus_file(VERSION_FULL_CONFIG);
	return GDMonoMarshal::mono_string_from_mesh(full_templates_dir);
}

MonoString *mesh_icall_Internal_SimplifyMeshPath(MonoString *p_path) {
	String path = GDMonoMarshal::mono_string_to_mesh(p_path);
	return GDMonoMarshal::mono_string_from_mesh(path.simplify_path());
}

MonoBoolean mesh_icall_Internal_IsOsxAppBundleInstalled(MonoString *p_bundle_id) {
#ifdef OSX_ENABLED
	String bundle_id = GDMonoMarshal::mono_string_to_mesh(p_bundle_id);
	return (MonoBoolean)osx_is_app_bundle_installed(bundle_id);
#else
	(void)p_bundle_id; // UNUSED
	return (MonoBoolean) false;
#endif
}

MonoBoolean mesh_icall_Internal_MeshIs32Bits() {
	return sizeof(void *) == 4;
}

MonoBoolean mesh_icall_Internal_MeshIsRealTDouble() {
#ifdef REAL_T_IS_DOUBLE
	return (MonoBoolean) true;
#else
	return (MonoBoolean) false;
#endif
}

void mesh_icall_Internal_MeshMainIteration() {
	Main::iteration();
}

uint64_t mesh_icall_Internal_GetCoreApiHash() {
	return ClassDB::get_api_hash(ClassDB::API_CORE);
}

uint64_t mesh_icall_Internal_GetEditorApiHash() {
	return ClassDB::get_api_hash(ClassDB::API_EDITOR);
}

MonoBoolean mesh_icall_Internal_IsAssembliesReloadingNeeded() {
#ifdef GD_MONO_HOT_RELOAD
	return (MonoBoolean)CSharpLanguage::get_singleton()->is_assembly_reloading_needed();
#else
	return (MonoBoolean) false;
#endif
}

void mesh_icall_Internal_ReloadAssemblies(MonoBoolean p_soft_reload) {
#ifdef GD_MONO_HOT_RELOAD
	mono_bind::MeshSharp::get_singleton()->call_deferred(SNAME("_reload_assemblies"), (bool)p_soft_reload);
#endif
}

void mesh_icall_Internal_EditorDebuggerNodeReloadScripts() {
	EditorDebuggerNode::get_singleton()->reload_scripts();
}

MonoBoolean mesh_icall_Internal_ScriptEditorEdit(MonoObject *p_resource, int32_t p_line, int32_t p_col, MonoBoolean p_grab_focus) {
	Ref<Resource> resource = GDMonoMarshal::mono_object_to_variant(p_resource);
	return (MonoBoolean)ScriptEditor::get_singleton()->edit(resource, p_line, p_col, (bool)p_grab_focus);
}

void mesh_icall_Internal_EditorNodeShowScriptScreen() {
	EditorNode::get_singleton()->call("_editor_select", EditorNode::EDITOR_SCRIPT);
}

MonoString *mesh_icall_Internal_MonoWindowsInstallRoot() {
#ifdef WINDOWS_ENABLED
	String install_root_dir = GDMono::get_singleton()->get_mono_reg_info().install_root_dir;
	return GDMonoMarshal::mono_string_from_mesh(install_root_dir);
#else
	return nullptr;
#endif
}

void mesh_icall_Internal_EditorRunPlay() {
	EditorNode::get_singleton()->run_play();
}

void mesh_icall_Internal_EditorRunStop() {
	EditorNode::get_singleton()->run_stop();
}

void mesh_icall_Internal_ScriptEditorDebugger_ReloadScripts() {
	EditorDebuggerNode *ed = EditorDebuggerNode::get_singleton();
	if (ed) {
		ed->reload_scripts();
	}
}

MonoArray *mesh_icall_Internal_CodeCompletionRequest(int32_t p_kind, MonoString *p_script_file) {
	String script_file = GDMonoMarshal::mono_string_to_mesh(p_script_file);
	PackedStringArray suggestions = gdmono::get_code_completion((gdmono::CompletionKind)p_kind, script_file);
	return GDMonoMarshal::PackedStringArray_to_mono_array(suggestions);
}

float mesh_icall_Globals_EditorScale() {
	return EDSCALE;
}

MonoObject *mesh_icall_Globals_GlobalDef(MonoString *p_setting, MonoObject *p_default_value, MonoBoolean p_restart_if_changed) {
	String setting = GDMonoMarshal::mono_string_to_mesh(p_setting);
	Variant default_value = GDMonoMarshal::mono_object_to_variant(p_default_value);
	Variant result = _GLOBAL_DEF(setting, default_value, (bool)p_restart_if_changed);
	return GDMonoMarshal::variant_to_mono_object(result);
}

MonoObject *mesh_icall_Globals_EditorDef(MonoString *p_setting, MonoObject *p_default_value, MonoBoolean p_restart_if_changed) {
	String setting = GDMonoMarshal::mono_string_to_mesh(p_setting);
	Variant default_value = GDMonoMarshal::mono_object_to_variant(p_default_value);
	Variant result = _EDITOR_DEF(setting, default_value, (bool)p_restart_if_changed);
	return GDMonoMarshal::variant_to_mono_object(result);
}

MonoObject *mesh_icall_Globals_EditorShortcut(MonoString *p_setting) {
	String setting = GDMonoMarshal::mono_string_to_mesh(p_setting);
	Ref<Shortcut> result = ED_GET_SHORTCUT(setting);
	return GDMonoMarshal::variant_to_mono_object(result);
}

MonoString *mesh_icall_Globals_TTR(MonoString *p_text) {
	String text = GDMonoMarshal::mono_string_to_mesh(p_text);
	return GDMonoMarshal::mono_string_from_mesh(TTR(text));
}

MonoString *mesh_icall_Utils_OS_GetPlatformName() {
	String os_name = OS::get_singleton()->get_name();
	return GDMonoMarshal::mono_string_from_mesh(os_name);
}

MonoBoolean mesh_icall_Utils_OS_UnixFileHasExecutableAccess(MonoString *p_file_path) {
#ifdef UNIX_ENABLED
	String file_path = GDMonoMarshal::mono_string_to_mesh(p_file_path);
	return access(file_path.utf8().get_data(), X_OK) == 0;
#else
	ERR_FAIL_V(false);
#endif
}

void register_editor_internal_calls() {
	// MeshSharpDirs
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_ResDataDir", mesh_icall_MeshSharpDirs_ResDataDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_ResMetadataDir", mesh_icall_MeshSharpDirs_ResMetadataDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_ResAssembliesBaseDir", mesh_icall_MeshSharpDirs_ResAssembliesBaseDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_ResAssembliesDir", mesh_icall_MeshSharpDirs_ResAssembliesDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_ResConfigDir", mesh_icall_MeshSharpDirs_ResConfigDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_ResTempDir", mesh_icall_MeshSharpDirs_ResTempDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_ResTempAssembliesBaseDir", mesh_icall_MeshSharpDirs_ResTempAssembliesBaseDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_ResTempAssembliesDir", mesh_icall_MeshSharpDirs_ResTempAssembliesDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_MonoUserDir", mesh_icall_MeshSharpDirs_MonoUserDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_MonoLogsDir", mesh_icall_MeshSharpDirs_MonoLogsDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_MonoSolutionsDir", mesh_icall_MeshSharpDirs_MonoSolutionsDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_BuildLogsDirs", mesh_icall_MeshSharpDirs_BuildLogsDirs);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_ProjectSlnPath", mesh_icall_MeshSharpDirs_ProjectSlnPath);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_ProjectCsProjPath", mesh_icall_MeshSharpDirs_ProjectCsProjPath);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_DataEditorToolsDir", mesh_icall_MeshSharpDirs_DataEditorToolsDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_DataEditorPrebuiltApiDir", mesh_icall_MeshSharpDirs_DataEditorPrebuiltApiDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_DataMonoEtcDir", mesh_icall_MeshSharpDirs_DataMonoEtcDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_DataMonoLibDir", mesh_icall_MeshSharpDirs_DataMonoLibDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.MeshSharpDirs::internal_DataMonoBinDir", mesh_icall_MeshSharpDirs_DataMonoBinDir);

	// EditorProgress
	GDMonoUtils::add_internal_call("MeshTools.Internals.EditorProgress::internal_Create", mesh_icall_EditorProgress_Create);
	GDMonoUtils::add_internal_call("MeshTools.Internals.EditorProgress::internal_Dispose", mesh_icall_EditorProgress_Dispose);
	GDMonoUtils::add_internal_call("MeshTools.Internals.EditorProgress::internal_Step", mesh_icall_EditorProgress_Step);

	// ExportPlugin
	GDMonoUtils::add_internal_call("MeshTools.Export.ExportPlugin::internal_GetExportedAssemblyDependencies", mesh_icall_ExportPlugin_GetExportedAssemblyDependencies);

	// Internals
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_UpdateApiAssembliesFromPrebuilt", mesh_icall_Internal_UpdateApiAssembliesFromPrebuilt);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_FullTemplatesDir", mesh_icall_Internal_FullTemplatesDir);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_SimplifyMeshPath", mesh_icall_Internal_SimplifyMeshPath);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_IsOsxAppBundleInstalled", mesh_icall_Internal_IsOsxAppBundleInstalled);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_MeshIs32Bits", mesh_icall_Internal_MeshIs32Bits);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_MeshIsRealTDouble", mesh_icall_Internal_MeshIsRealTDouble);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_MeshMainIteration", mesh_icall_Internal_MeshMainIteration);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_GetCoreApiHash", mesh_icall_Internal_GetCoreApiHash);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_GetEditorApiHash", mesh_icall_Internal_GetEditorApiHash);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_IsAssembliesReloadingNeeded", mesh_icall_Internal_IsAssembliesReloadingNeeded);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_ReloadAssemblies", mesh_icall_Internal_ReloadAssemblies);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_EditorDebuggerNodeReloadScripts", mesh_icall_Internal_EditorDebuggerNodeReloadScripts);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_ScriptEditorEdit", mesh_icall_Internal_ScriptEditorEdit);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_EditorNodeShowScriptScreen", mesh_icall_Internal_EditorNodeShowScriptScreen);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_MonoWindowsInstallRoot", mesh_icall_Internal_MonoWindowsInstallRoot);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_EditorRunPlay", mesh_icall_Internal_EditorRunPlay);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_EditorRunStop", mesh_icall_Internal_EditorRunStop);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_ScriptEditorDebugger_ReloadScripts", mesh_icall_Internal_ScriptEditorDebugger_ReloadScripts);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Internal::internal_CodeCompletionRequest", mesh_icall_Internal_CodeCompletionRequest);

	// Globals
	GDMonoUtils::add_internal_call("MeshTools.Internals.Globals::internal_EditorScale", mesh_icall_Globals_EditorScale);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Globals::internal_GlobalDef", mesh_icall_Globals_GlobalDef);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Globals::internal_EditorDef", mesh_icall_Globals_EditorDef);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Globals::internal_EditorShortcut", mesh_icall_Globals_EditorShortcut);
	GDMonoUtils::add_internal_call("MeshTools.Internals.Globals::internal_TTR", mesh_icall_Globals_TTR);

	// Utils.OS
	GDMonoUtils::add_internal_call("MeshTools.Utils.OS::GetPlatformName", mesh_icall_Utils_OS_GetPlatformName);
	GDMonoUtils::add_internal_call("MeshTools.Utils.OS::UnixFileHasExecutableAccess", mesh_icall_Utils_OS_UnixFileHasExecutableAccess);
}
