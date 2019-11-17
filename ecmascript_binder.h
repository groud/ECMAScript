#ifndef ECMASCRIPT_BINDING_HELPER_H
#define ECMASCRIPT_BINDING_HELPER_H

#include "ecmascript_gc_handler.h"

typedef ECMAScriptGCHandler ECMAMethodInfo;

struct ECMAProperyInfo {
	Variant::Type type;
	Variant default_value;
};

struct ECMAClassInfo {
	bool tool;
	StringName class_name;
	String icon_path;
	ECMAScriptGCHandler ecma_class_function;
	ECMAScriptGCHandler ecma_prototype;
	const ClassDB::ClassInfo *native_class;
	HashMap<StringName, MethodInfo> signals;
	HashMap<StringName, ECMAProperyInfo> properties;
};

class ECMAScriptBinder {
	friend class ECMAScript;

protected:
	HashMap<StringName, ECMAClassInfo> ecma_classes;

public:
	virtual void clear_classes() { ecma_classes.clear(); }

	virtual void initialize() = 0;
	virtual void uninitialize() = 0;

	virtual void *alloc_object_binding_data(Object *p_object) = 0;
	virtual void free_object_binding_data(void *p_gc_handle) = 0;

	virtual void godot_refcount_incremented(Reference *p_object) = 0;
	virtual bool godot_refcount_decremented(Reference *p_object) = 0;

	virtual Error eval_string(const String &p_source) = 0;
	virtual Error safe_eval_text(const String &p_source, String &r_error) = 0;

	virtual ECMAScriptGCHandler create_ecma_instance_for_godot_object(const StringName &ecma_class_name, Object *p_object) = 0;
	virtual Variant call_method(const ECMAScriptGCHandler &p_object, const StringName &p_method, const Variant **p_args, int p_argcount, Variant::CallError &r_error) = 0;
	virtual bool get_instance_property(const ECMAScriptGCHandler &p_object, const StringName &p_name, Variant &r_ret) = 0;
	virtual bool set_instance_property(const ECMAScriptGCHandler &p_object, const StringName &p_name, const Variant &p_value) = 0;
	virtual bool has_method(const ECMAScriptGCHandler &p_object, const StringName &p_name) = 0;
};

#endif