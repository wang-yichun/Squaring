#include "kompex_binding.hpp"
#include "cocos2d_specifics.hpp"
#include "KompexSQLitePrerequisites.h"
#include "KompexSQLiteDatabase.h"
#include "KompexSQLiteStatement.h"
#include "KompexSQLiteException.h"
#include "KompexSQLiteStreamRedirection.h"
#include "sqlite3.h"
#include "sqlite3ext.h"

template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	TypeTest<T> t;
	T* cobj = new T();
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	assert(p);
	JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
	js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));

	return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return JS_FALSE;
}


JSClass  *jsb_SQLiteDatabase_class;
JSObject *jsb_SQLiteDatabase_prototype;

JSBool js_kompex_binding_SQLiteDatabase_MoveDatabaseToMemory(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->MoveDatabaseToMemory();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 1) {
		Kompex::SQLiteDatabase::UtfEncoding arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->MoveDatabaseToMemory(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_GetLibVersionNumber(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->GetLibVersionNumber();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_InterruptDatabaseOperation(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->InterruptDatabaseOperation();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_ActivateProfiling(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->ActivateProfiling();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_ActivateTracing(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->ActivateTracing();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_GetLastInsertRowId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		long long ret = cobj->GetLastInsertRowId();
		jsval jsret;
		jsret = long_long_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_GetAutoCommit(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->GetAutoCommit();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_GetMemoryUsage(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		long long ret = cobj->GetMemoryUsage();
		jsval jsret;
		jsret = long_long_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_SaveDatabaseFromMemoryToFile(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteDatabase* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			cobj->SaveDatabaseFromMemoryToFile(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 0) {
			cobj->SaveDatabaseFromMemoryToFile();
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->SaveDatabaseFromMemoryToFile(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_GetMemoryHighwaterMark(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		long long ret = cobj->GetMemoryHighwaterMark();
		jsval jsret;
		jsret = long_long_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		long long ret = cobj->GetMemoryHighwaterMark(arg0);
		jsval jsret;
		jsret = long_long_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_GetDatabaseChanges(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->GetDatabaseChanges();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_GetTotalDatabaseChanges(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->GetTotalDatabaseChanges();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_GetDatabaseHandle(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		sqlite3* ret = cobj->GetDatabaseHandle();
		jsval jsret;
		#pragma warning NO CONVERSION FROM NATIVE FOR sqlite3*;
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_IsDatabaseReadOnly(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->IsDatabaseReadOnly();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_Close(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->Close();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_ReleaseMemory(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteDatabase* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 0) {
			cobj->ReleaseMemory();
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->ReleaseMemory(arg0);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_Open(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteDatabase* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 3) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = JS_TRUE; break; }
			const char* arg2;
			std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			cobj->Open(arg0, arg1, arg2);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 3) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = JS_TRUE; break; }
			const char* arg2;
			std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			cobj->Open(arg0, arg1, arg2);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			cobj->Open(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_SetSoftHeapLimit(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteDatabase* cobj = (Kompex::SQLiteDatabase *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->SetSoftHeapLimit(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteDatabase_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteDatabase* cobj = NULL;
	do {
		if (argc == 3) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = JS_TRUE; break; }
			const char* arg2;
			std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			cobj = new Kompex::SQLiteDatabase(arg0, arg1, arg2);
			TypeTest<Kompex::SQLiteDatabase> t;
			js_type_class_t *typeClass;
			uint32_t typeId = t.s_id();
			HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
			assert(typeClass);
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* proxy = jsb_new_proxy(cobj, obj);
		}
	} while(0);

	do {
		if (argc == 0) {
			cobj = new Kompex::SQLiteDatabase();
			TypeTest<Kompex::SQLiteDatabase> t;
			js_type_class_t *typeClass;
			uint32_t typeId = t.s_id();
			HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
			assert(typeClass);
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* proxy = jsb_new_proxy(cobj, obj);
		}
	} while(0);

	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = JS_TRUE; break; }
			cobj = new Kompex::SQLiteDatabase(arg0, arg1);
			TypeTest<Kompex::SQLiteDatabase> t;
			js_type_class_t *typeClass;
			uint32_t typeId = t.s_id();
			HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
			assert(typeClass);
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* proxy = jsb_new_proxy(cobj, obj);
		}
	} while(0);

	do {
		if (argc == 3) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = JS_TRUE; break; }
			const char* arg2;
			std::string arg2_tmp; ok &= jsval_to_std_string(cx, argv[2], &arg2_tmp); arg2 = arg2_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			cobj = new Kompex::SQLiteDatabase(arg0, arg1, arg2);
			TypeTest<Kompex::SQLiteDatabase> t;
			js_type_class_t *typeClass;
			uint32_t typeId = t.s_id();
			HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
			assert(typeClass);
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* proxy = jsb_new_proxy(cobj, obj);
		}
	} while(0);

	do {
		if (argc == 2) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = JS_TRUE; break; }
			cobj = new Kompex::SQLiteDatabase(arg0, arg1);
			TypeTest<Kompex::SQLiteDatabase> t;
			js_type_class_t *typeClass;
			uint32_t typeId = t.s_id();
			HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
			assert(typeClass);
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* proxy = jsb_new_proxy(cobj, obj);
		}
	} while(0);

	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			cobj = new Kompex::SQLiteDatabase(arg0);
			TypeTest<Kompex::SQLiteDatabase> t;
			js_type_class_t *typeClass;
			uint32_t typeId = t.s_id();
			HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
			assert(typeClass);
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* proxy = jsb_new_proxy(cobj, obj);
		}
	} while(0);

	if (cobj) {
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}




void js_kompex_binding_SQLiteDatabase_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SQLiteDatabase)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        Kompex::SQLiteDatabase *nobj = static_cast<Kompex::SQLiteDatabase *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

static JSBool js_kompex_binding_SQLiteDatabase_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    Kompex::SQLiteDatabase *nobj = new Kompex::SQLiteDatabase();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_kompex_binding_SQLiteDatabase(JSContext *cx, JSObject *global) {
	jsb_SQLiteDatabase_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_SQLiteDatabase_class->name = "SQLiteDatabase";
	jsb_SQLiteDatabase_class->addProperty = JS_PropertyStub;
	jsb_SQLiteDatabase_class->delProperty = JS_PropertyStub;
	jsb_SQLiteDatabase_class->getProperty = JS_PropertyStub;
	jsb_SQLiteDatabase_class->setProperty = JS_StrictPropertyStub;
	jsb_SQLiteDatabase_class->enumerate = JS_EnumerateStub;
	jsb_SQLiteDatabase_class->resolve = JS_ResolveStub;
	jsb_SQLiteDatabase_class->convert = JS_ConvertStub;
	jsb_SQLiteDatabase_class->finalize = js_kompex_binding_SQLiteDatabase_finalize;
	jsb_SQLiteDatabase_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("MoveDatabaseToMemory", js_kompex_binding_SQLiteDatabase_MoveDatabaseToMemory, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetLibVersionNumber", js_kompex_binding_SQLiteDatabase_GetLibVersionNumber, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("InterruptDatabaseOperation", js_kompex_binding_SQLiteDatabase_InterruptDatabaseOperation, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ActivateProfiling", js_kompex_binding_SQLiteDatabase_ActivateProfiling, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ActivateTracing", js_kompex_binding_SQLiteDatabase_ActivateTracing, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetLastInsertRowId", js_kompex_binding_SQLiteDatabase_GetLastInsertRowId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetAutoCommit", js_kompex_binding_SQLiteDatabase_GetAutoCommit, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetMemoryUsage", js_kompex_binding_SQLiteDatabase_GetMemoryUsage, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("SaveDatabaseFromMemoryToFile", js_kompex_binding_SQLiteDatabase_SaveDatabaseFromMemoryToFile, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetMemoryHighwaterMark", js_kompex_binding_SQLiteDatabase_GetMemoryHighwaterMark, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetDatabaseChanges", js_kompex_binding_SQLiteDatabase_GetDatabaseChanges, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetTotalDatabaseChanges", js_kompex_binding_SQLiteDatabase_GetTotalDatabaseChanges, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetDatabaseHandle", js_kompex_binding_SQLiteDatabase_GetDatabaseHandle, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("IsDatabaseReadOnly", js_kompex_binding_SQLiteDatabase_IsDatabaseReadOnly, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("Close", js_kompex_binding_SQLiteDatabase_Close, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ReleaseMemory", js_kompex_binding_SQLiteDatabase_ReleaseMemory, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("Open", js_kompex_binding_SQLiteDatabase_Open, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("SetSoftHeapLimit", js_kompex_binding_SQLiteDatabase_SetSoftHeapLimit, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_kompex_binding_SQLiteDatabase_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_SQLiteDatabase_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_SQLiteDatabase_class,
		js_kompex_binding_SQLiteDatabase_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "SQLiteDatabase", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<Kompex::SQLiteDatabase> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_SQLiteDatabase_class;
		p->proto = jsb_SQLiteDatabase_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_SQLiteStatement_class;
JSObject *jsb_SQLiteStatement_prototype;

JSBool js_kompex_binding_SQLiteStatement_GetSqlResultCString(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			const unsigned char* ret = cobj->GetSqlResultCString(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const unsigned char*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			const unsigned char* arg1;
			#pragma warning NO CONVERSION TO NATIVE FOR const unsigned char*;
			if (!ok) { ok = JS_TRUE; break; }
			const unsigned char* ret = cobj->GetSqlResultCString(arg0, arg1);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const unsigned char*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const unsigned char* ret = cobj->GetSqlResultCString(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const unsigned char*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const unsigned char* arg1;
			#pragma warning NO CONVERSION TO NATIVE FOR const unsigned char*;
			if (!ok) { ok = JS_TRUE; break; }
			const unsigned char* ret = cobj->GetSqlResultCString(arg0, arg1);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const unsigned char*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			const unsigned char* ret = cobj->GetSqlResultCString(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const unsigned char*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			const unsigned char* arg1;
			#pragma warning NO CONVERSION TO NATIVE FOR const unsigned char*;
			if (!ok) { ok = JS_TRUE; break; }
			const unsigned char* ret = cobj->GetSqlResultCString(arg0, arg1);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const unsigned char*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnTableName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const char* ret = cobj->GetColumnTableName(arg0);
			jsval jsret;
			jsret = c_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const char* ret = cobj->GetColumnTableName(arg0);
			jsval jsret;
			jsret = c_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const char* ret = cobj->GetColumnName(arg0);
			jsval jsret;
			jsret = c_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const char* ret = cobj->GetColumnName(arg0);
			jsval jsret;
			jsret = c_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_BindDouble(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		int arg0;
		double arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		ok &= JS_ValueToNumber(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->BindDouble(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetDataCount(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->GetDataCount();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_BindZeroBlob(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		int arg0;
		int arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->BindZeroBlob(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetSqlResultInt(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetSqlResultInt(arg0);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetSqlResultInt(arg0, arg1);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetSqlResultInt(arg0);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetSqlResultInt(arg0, arg1);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetSqlResultInt(arg0);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			int arg1;
			ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetSqlResultInt(arg0, arg1);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_BindBlob(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		int arg0;
		const void* arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		#pragma warning NO CONVERSION TO NATIVE FOR const void*;
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->BindBlob(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 3) {
		int arg0;
		const void* arg1;
		int arg2;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		#pragma warning NO CONVERSION TO NATIVE FOR const void*;
		ok &= jsval_to_int32(cx, argv[2], (int32_t *)&arg2);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->BindBlob(arg0, arg1, arg2);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnInt(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetColumnInt(arg0);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetColumnInt(arg0);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnBlob(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const void* ret = cobj->GetColumnBlob(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const void*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const void* ret = cobj->GetColumnBlob(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const void*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_FetchRow(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->FetchRow();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnOriginName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const char* ret = cobj->GetColumnOriginName(arg0);
			jsval jsret;
			jsret = c_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const char* ret = cobj->GetColumnOriginName(arg0);
			jsval jsret;
			jsret = c_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_BindInt(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		int arg0;
		int arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->BindInt(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnInt64(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			long long ret = cobj->GetColumnInt64(arg0);
			jsval jsret;
			jsret = long_long_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			long long ret = cobj->GetColumnInt64(arg0);
			jsval jsret;
			jsret = long_long_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnDeclaredDatatype16(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetColumnDeclaredDatatype16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetColumnDeclaredDatatype16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetTableColumnMetadata(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		std::string arg0;
		std::string arg1;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		ok &= jsval_to_std_string(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->GetTableColumnMetadata(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetSqlResultDouble(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			double ret = cobj->GetSqlResultDouble(arg0);
			jsval jsret;
			jsret = DOUBLE_TO_JSVAL(ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			double arg1;
			ok &= JS_ValueToNumber(cx, argv[1], &arg1);
			if (!ok) { ok = JS_TRUE; break; }
			double ret = cobj->GetSqlResultDouble(arg0, arg1);
			jsval jsret;
			jsret = DOUBLE_TO_JSVAL(ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			double ret = cobj->GetSqlResultDouble(arg0);
			jsval jsret;
			jsret = DOUBLE_TO_JSVAL(ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			double arg1;
			ok &= JS_ValueToNumber(cx, argv[1], &arg1);
			if (!ok) { ok = JS_TRUE; break; }
			double ret = cobj->GetSqlResultDouble(arg0, arg1);
			jsval jsret;
			jsret = DOUBLE_TO_JSVAL(ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			double ret = cobj->GetSqlResultDouble(arg0);
			jsval jsret;
			jsret = DOUBLE_TO_JSVAL(ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			double arg1;
			ok &= JS_ValueToNumber(cx, argv[1], &arg1);
			if (!ok) { ok = JS_TRUE; break; }
			double ret = cobj->GetSqlResultDouble(arg0, arg1);
			jsval jsret;
			jsret = DOUBLE_TO_JSVAL(ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_BeginTransaction(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->BeginTransaction();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnDatabaseName16(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetColumnDatabaseName16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetColumnDatabaseName16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnString(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			std::string ret = cobj->GetColumnString(arg0);
			jsval jsret;
			jsret = std_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			std::string ret = cobj->GetColumnString(arg0);
			jsval jsret;
			jsret = std_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_BindInt64(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		int arg0;
		long long arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		ok &= jsval_to_long_long(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->BindInt64(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnDouble(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			double ret = cobj->GetColumnDouble(arg0);
			jsval jsret;
			jsret = DOUBLE_TO_JSVAL(ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			double ret = cobj->GetColumnDouble(arg0);
			jsval jsret;
			jsret = DOUBLE_TO_JSVAL(ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnOriginName16(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetColumnOriginName16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetColumnOriginName16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetSqlResultBlob(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			const void* ret = cobj->GetSqlResultBlob(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const void*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			const void* arg1;
			#pragma warning NO CONVERSION TO NATIVE FOR const void*;
			if (!ok) { ok = JS_TRUE; break; }
			const void* ret = cobj->GetSqlResultBlob(arg0, arg1);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const void*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const void* ret = cobj->GetSqlResultBlob(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const void*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const void* arg1;
			#pragma warning NO CONVERSION TO NATIVE FOR const void*;
			if (!ok) { ok = JS_TRUE; break; }
			const void* ret = cobj->GetSqlResultBlob(arg0, arg1);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const void*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			const void* ret = cobj->GetSqlResultBlob(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const void*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			const void* arg1;
			#pragma warning NO CONVERSION TO NATIVE FOR const void*;
			if (!ok) { ok = JS_TRUE; break; }
			const void* ret = cobj->GetSqlResultBlob(arg0, arg1);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const void*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_BindNull(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->BindNull(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_Sql(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			cobj->Sql(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->Sql(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	

	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			cobj->Sql(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_SqlAggregateFuncResult(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			float ret = cobj->SqlAggregateFuncResult(arg0);
			jsval jsret;
			jsret = DOUBLE_TO_JSVAL(ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			float ret = cobj->SqlAggregateFuncResult(arg0);
			jsval jsret;
			jsret = DOUBLE_TO_JSVAL(ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			float ret = cobj->SqlAggregateFuncResult(arg0);
			jsval jsret;
			jsret = DOUBLE_TO_JSVAL(ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnName16(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetColumnName16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetColumnName16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_Reset(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->Reset();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_Execute(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->Execute();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_Transaction(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->Transaction(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			cobj->Transaction(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			cobj->Transaction(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_BindBool(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		int arg0;
		JSBool arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		ok &= JS_ValueToBoolean(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->BindBool(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnCString(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const unsigned char* ret = cobj->GetColumnCString(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const unsigned char*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const unsigned char* ret = cobj->GetColumnCString(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR const unsigned char*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnType(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetColumnType(arg0);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetColumnType(arg0);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetNumberOfRows(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		unsigned int ret = cobj->GetNumberOfRows();
		jsval jsret;
		jsret = uint32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnTableName16(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetColumnTableName16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetColumnTableName16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_RollbackTransaction(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->RollbackTransaction();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_BindString(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		int arg0;
		std::string arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		ok &= jsval_to_std_string(cx, argv[1], &arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->BindString(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_FreeQuery(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->FreeQuery();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_SqlStatement(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			cobj->SqlStatement(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->SqlStatement(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	

	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			cobj->SqlStatement(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_BindString16(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		int arg0;
		const wchar_t* arg1;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->BindString16(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnBool(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			bool ret = cobj->GetColumnBool(arg0);
			jsval jsret;
			jsret = BOOLEAN_TO_JSVAL(ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			bool ret = cobj->GetColumnBool(arg0);
			jsval jsret;
			jsret = BOOLEAN_TO_JSVAL(ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_ExecuteAndFree(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->ExecuteAndFree();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetSqlResultString16(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetSqlResultString16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* arg1;
			#pragma warning NO CONVERSION TO NATIVE FOR wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetSqlResultString16(arg0, arg1);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetSqlResultString16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* arg1;
			#pragma warning NO CONVERSION TO NATIVE FOR wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetSqlResultString16(arg0, arg1);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetSqlResultString16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* arg1;
			#pragma warning NO CONVERSION TO NATIVE FOR wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetSqlResultString16(arg0, arg1);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnDeclaredDatatype(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const char* ret = cobj->GetColumnDeclaredDatatype(arg0);
			jsval jsret;
			jsret = c_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const char* ret = cobj->GetColumnDeclaredDatatype(arg0);
			jsval jsret;
			jsret = c_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetSqlResultString(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			std::string ret = cobj->GetSqlResultString(arg0);
			jsval jsret;
			jsret = std_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			std::string arg1;
			ok &= jsval_to_std_string(cx, argv[1], &arg1);
			if (!ok) { ok = JS_TRUE; break; }
			std::string ret = cobj->GetSqlResultString(arg0, arg1);
			jsval jsret;
			jsret = std_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			std::string ret = cobj->GetSqlResultString(arg0);
			jsval jsret;
			jsret = std_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			std::string arg1;
			ok &= jsval_to_std_string(cx, argv[1], &arg1);
			if (!ok) { ok = JS_TRUE; break; }
			std::string ret = cobj->GetSqlResultString(arg0, arg1);
			jsval jsret;
			jsret = std_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			std::string ret = cobj->GetSqlResultString(arg0);
			jsval jsret;
			jsret = std_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			std::string arg1;
			ok &= jsval_to_std_string(cx, argv[1], &arg1);
			if (!ok) { ok = JS_TRUE; break; }
			std::string ret = cobj->GetSqlResultString(arg0, arg1);
			jsval jsret;
			jsret = std_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnBytes(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetColumnBytes(arg0);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetColumnBytes(arg0);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnBytes16(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetColumnBytes16(arg0);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			int ret = cobj->GetColumnBytes16(arg0);
			jsval jsret;
			jsret = int32_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnDatabaseName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const char* ret = cobj->GetColumnDatabaseName(arg0);
			jsval jsret;
			jsret = c_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			const char* ret = cobj->GetColumnDatabaseName(arg0);
			jsval jsret;
			jsret = c_string_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnCount(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->GetColumnCount();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_ClearBindings(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->ClearBindings();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetTable(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->GetTable(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		std::string arg0;
		unsigned short arg1;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		#pragma warning NO CONVERSION TO NATIVE FOR unsigned short;
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->GetTable(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetSqlResultInt64(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			long long ret = cobj->GetSqlResultInt64(arg0);
			jsval jsret;
			jsret = long_long_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			long long arg1;
			ok &= jsval_to_long_long(cx, argv[1], &arg1);
			if (!ok) { ok = JS_TRUE; break; }
			long long ret = cobj->GetSqlResultInt64(arg0, arg1);
			jsval jsret;
			jsret = long_long_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			long long ret = cobj->GetSqlResultInt64(arg0);
			jsval jsret;
			jsret = long_long_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			long long arg1;
			ok &= jsval_to_long_long(cx, argv[1], &arg1);
			if (!ok) { ok = JS_TRUE; break; }
			long long ret = cobj->GetSqlResultInt64(arg0, arg1);
			jsval jsret;
			jsret = long_long_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			long long ret = cobj->GetSqlResultInt64(arg0);
			jsval jsret;
			jsret = long_long_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 2) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			long long arg1;
			ok &= jsval_to_long_long(cx, argv[1], &arg1);
			if (!ok) { ok = JS_TRUE; break; }
			long long ret = cobj->GetSqlResultInt64(arg0, arg1);
			jsval jsret;
			jsret = long_long_to_jsval(cx, ret);
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_SecureTransaction(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->SecureTransaction(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const char* arg0;
			std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
			if (!ok) { ok = JS_TRUE; break; }
			cobj->SecureTransaction(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			const wchar_t* arg0;
			#pragma warning NO CONVERSION TO NATIVE FOR const wchar_t*;
			if (!ok) { ok = JS_TRUE; break; }
			cobj->SecureTransaction(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_GetColumnString16(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetColumnString16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 1) {
			int arg0;
			ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
			if (!ok) { ok = JS_TRUE; break; }
			wchar_t* ret = cobj->GetColumnString16(arg0);
			jsval jsret;
			#pragma warning NO CONVERSION FROM NATIVE FOR wchar_t*;
			JS_SET_RVAL(cx, vp, jsret);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_CommitTransaction(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	Kompex::SQLiteStatement* cobj = (Kompex::SQLiteStatement *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->CommitTransaction();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_kompex_binding_SQLiteStatement_constructor(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	Kompex::SQLiteStatement* cobj = NULL;
	do {
		if (argc == 1) {
			Kompex::SQLiteDatabase* arg0;
			do {
				if (!argv[0].isObject()) { ok = JS_FALSE; break; }
				js_proxy_t *proxy;
				JSObject *tmpObj = JSVAL_TO_OBJECT(argv[0]);
				proxy = jsb_get_js_proxy(tmpObj);
				arg0 = (Kompex::SQLiteDatabase*)(proxy ? proxy->ptr : NULL);
				JSB_PRECONDITION2( arg0, cx, JS_FALSE, "Invalid Native Object");
			} while (0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj = new Kompex::SQLiteStatement(arg0);
			TypeTest<Kompex::SQLiteStatement> t;
			js_type_class_t *typeClass;
			uint32_t typeId = t.s_id();
			HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
			assert(typeClass);
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* proxy = jsb_new_proxy(cobj, obj);
		}
	} while(0);

	do {
		if (argc == 0) {
			cobj = new Kompex::SQLiteStatement();
			TypeTest<Kompex::SQLiteStatement> t;
			js_type_class_t *typeClass;
			uint32_t typeId = t.s_id();
			HASH_FIND_INT(_js_global_type_ht, &typeId, typeClass);
			assert(typeClass);
			obj = JS_NewObject(cx, typeClass->jsclass, typeClass->proto, typeClass->parentProto);
			js_proxy_t* proxy = jsb_new_proxy(cobj, obj);
		}
	} while(0);

	if (cobj) {
		JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(obj));
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}




void js_kompex_binding_SQLiteStatement_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (SQLiteStatement)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        Kompex::SQLiteStatement *nobj = static_cast<Kompex::SQLiteStatement *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

static JSBool js_kompex_binding_SQLiteStatement_ctor(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    Kompex::SQLiteStatement *nobj = new Kompex::SQLiteStatement();
    js_proxy_t* p = jsb_new_proxy(nobj, obj);
    JS_SET_RVAL(cx, vp, JSVAL_VOID);
    return JS_TRUE;
}

void js_register_kompex_binding_SQLiteStatement(JSContext *cx, JSObject *global) {
	jsb_SQLiteStatement_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_SQLiteStatement_class->name = "SQLiteStatement";
	jsb_SQLiteStatement_class->addProperty = JS_PropertyStub;
	jsb_SQLiteStatement_class->delProperty = JS_PropertyStub;
	jsb_SQLiteStatement_class->getProperty = JS_PropertyStub;
	jsb_SQLiteStatement_class->setProperty = JS_StrictPropertyStub;
	jsb_SQLiteStatement_class->enumerate = JS_EnumerateStub;
	jsb_SQLiteStatement_class->resolve = JS_ResolveStub;
	jsb_SQLiteStatement_class->convert = JS_ConvertStub;
	jsb_SQLiteStatement_class->finalize = js_kompex_binding_SQLiteStatement_finalize;
	jsb_SQLiteStatement_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("GetSqlResultCString", js_kompex_binding_SQLiteStatement_GetSqlResultCString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnTableName", js_kompex_binding_SQLiteStatement_GetColumnTableName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnName", js_kompex_binding_SQLiteStatement_GetColumnName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("BindDouble", js_kompex_binding_SQLiteStatement_BindDouble, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetDataCount", js_kompex_binding_SQLiteStatement_GetDataCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("BindZeroBlob", js_kompex_binding_SQLiteStatement_BindZeroBlob, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetSqlResultInt", js_kompex_binding_SQLiteStatement_GetSqlResultInt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("BindBlob", js_kompex_binding_SQLiteStatement_BindBlob, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnInt", js_kompex_binding_SQLiteStatement_GetColumnInt, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnBlob", js_kompex_binding_SQLiteStatement_GetColumnBlob, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("FetchRow", js_kompex_binding_SQLiteStatement_FetchRow, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnOriginName", js_kompex_binding_SQLiteStatement_GetColumnOriginName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("BindInt", js_kompex_binding_SQLiteStatement_BindInt, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnInt64", js_kompex_binding_SQLiteStatement_GetColumnInt64, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnDeclaredDatatype16", js_kompex_binding_SQLiteStatement_GetColumnDeclaredDatatype16, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetTableColumnMetadata", js_kompex_binding_SQLiteStatement_GetTableColumnMetadata, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetSqlResultDouble", js_kompex_binding_SQLiteStatement_GetSqlResultDouble, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("BeginTransaction", js_kompex_binding_SQLiteStatement_BeginTransaction, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnDatabaseName16", js_kompex_binding_SQLiteStatement_GetColumnDatabaseName16, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnString", js_kompex_binding_SQLiteStatement_GetColumnString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("BindInt64", js_kompex_binding_SQLiteStatement_BindInt64, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnDouble", js_kompex_binding_SQLiteStatement_GetColumnDouble, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnOriginName16", js_kompex_binding_SQLiteStatement_GetColumnOriginName16, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetSqlResultBlob", js_kompex_binding_SQLiteStatement_GetSqlResultBlob, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("BindNull", js_kompex_binding_SQLiteStatement_BindNull, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("Sql", js_kompex_binding_SQLiteStatement_Sql, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("SqlAggregateFuncResult", js_kompex_binding_SQLiteStatement_SqlAggregateFuncResult, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnName16", js_kompex_binding_SQLiteStatement_GetColumnName16, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("Reset", js_kompex_binding_SQLiteStatement_Reset, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("Execute", js_kompex_binding_SQLiteStatement_Execute, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("Transaction", js_kompex_binding_SQLiteStatement_Transaction, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("BindBool", js_kompex_binding_SQLiteStatement_BindBool, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnCString", js_kompex_binding_SQLiteStatement_GetColumnCString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnType", js_kompex_binding_SQLiteStatement_GetColumnType, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetNumberOfRows", js_kompex_binding_SQLiteStatement_GetNumberOfRows, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnTableName16", js_kompex_binding_SQLiteStatement_GetColumnTableName16, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("RollbackTransaction", js_kompex_binding_SQLiteStatement_RollbackTransaction, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("BindString", js_kompex_binding_SQLiteStatement_BindString, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("FreeQuery", js_kompex_binding_SQLiteStatement_FreeQuery, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("SqlStatement", js_kompex_binding_SQLiteStatement_SqlStatement, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("BindString16", js_kompex_binding_SQLiteStatement_BindString16, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnBool", js_kompex_binding_SQLiteStatement_GetColumnBool, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ExecuteAndFree", js_kompex_binding_SQLiteStatement_ExecuteAndFree, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetSqlResultString16", js_kompex_binding_SQLiteStatement_GetSqlResultString16, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnDeclaredDatatype", js_kompex_binding_SQLiteStatement_GetColumnDeclaredDatatype, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetSqlResultString", js_kompex_binding_SQLiteStatement_GetSqlResultString, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnBytes", js_kompex_binding_SQLiteStatement_GetColumnBytes, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnBytes16", js_kompex_binding_SQLiteStatement_GetColumnBytes16, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnDatabaseName", js_kompex_binding_SQLiteStatement_GetColumnDatabaseName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnCount", js_kompex_binding_SQLiteStatement_GetColumnCount, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("ClearBindings", js_kompex_binding_SQLiteStatement_ClearBindings, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetTable", js_kompex_binding_SQLiteStatement_GetTable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetSqlResultInt64", js_kompex_binding_SQLiteStatement_GetSqlResultInt64, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("SecureTransaction", js_kompex_binding_SQLiteStatement_SecureTransaction, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("GetColumnString16", js_kompex_binding_SQLiteStatement_GetColumnString16, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("CommitTransaction", js_kompex_binding_SQLiteStatement_CommitTransaction, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("ctor", js_kompex_binding_SQLiteStatement_ctor, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_SQLiteStatement_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_SQLiteStatement_class,
		js_kompex_binding_SQLiteStatement_constructor, 0, // constructor
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "SQLiteStatement", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<Kompex::SQLiteStatement> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_SQLiteStatement_class;
		p->proto = jsb_SQLiteStatement_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

void register_all_kompex_binding(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, obj, "kompex", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "kompex", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	js_register_kompex_binding_SQLiteStatement(cx, obj);
	js_register_kompex_binding_SQLiteDatabase(cx, obj);
}

