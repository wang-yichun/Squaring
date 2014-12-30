#ifndef __kompex_binding_h__
#define __kompex_binding_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_SQLiteDatabase_class;
extern JSObject *jsb_SQLiteDatabase_prototype;

JSBool js_kompex_binding_SQLiteDatabase_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_kompex_binding_SQLiteDatabase_finalize(JSContext *cx, JSObject *obj);
void js_register_kompex_binding_SQLiteDatabase(JSContext *cx, JSObject *global);
void register_all_kompex_binding(JSContext* cx, JSObject* obj);
JSBool js_kompex_binding_SQLiteDatabase_MoveDatabaseToMemory(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_GetLibVersionNumber(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_InterruptDatabaseOperation(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_ActivateProfiling(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_ActivateTracing(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_GetLastInsertRowId(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_GetAutoCommit(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_GetMemoryUsage(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_SaveDatabaseFromMemoryToFile(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_GetMemoryHighwaterMark(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_GetDatabaseChanges(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_GetTotalDatabaseChanges(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_GetDatabaseHandle(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_IsDatabaseReadOnly(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_Close(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_ReleaseMemory(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_Open(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_SetSoftHeapLimit(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteDatabase_SQLiteDatabase(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_SQLiteStatement_class;
extern JSObject *jsb_SQLiteStatement_prototype;

JSBool js_kompex_binding_SQLiteStatement_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_kompex_binding_SQLiteStatement_finalize(JSContext *cx, JSObject *obj);
void js_register_kompex_binding_SQLiteStatement(JSContext *cx, JSObject *global);
void register_all_kompex_binding(JSContext* cx, JSObject* obj);
JSBool js_kompex_binding_SQLiteStatement_GetSqlResultCString(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnTableName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_BindDouble(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetDataCount(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_BindZeroBlob(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetSqlResultInt(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_BindBlob(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnInt(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnBlob(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_FetchRow(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnOriginName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_BindInt(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnInt64(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnDeclaredDatatype16(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetTableColumnMetadata(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetSqlResultDouble(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_BeginTransaction(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnDatabaseName16(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnString(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_BindInt64(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnDouble(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnOriginName16(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetSqlResultBlob(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_BindNull(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_Sql(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_SqlAggregateFuncResult(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnName16(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_Reset(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_Execute(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_Transaction(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_BindBool(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnCString(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnType(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetNumberOfRows(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnTableName16(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_RollbackTransaction(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_BindString(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_FreeQuery(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_SqlStatement(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_BindString16(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnBool(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_ExecuteAndFree(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetSqlResultString16(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnDeclaredDatatype(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetSqlResultString(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnBytes(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnBytes16(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnDatabaseName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnCount(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_ClearBindings(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetTable(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetSqlResultInt64(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_SecureTransaction(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_GetColumnString16(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_CommitTransaction(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_kompex_binding_SQLiteStatement_SQLiteStatement(JSContext *cx, uint32_t argc, jsval *vp);
#endif

