/**
 * @module kompex_binding
 */
var kompex = kompex || {};

/**
 * @class SQLiteDatabase
 */
kompex.SQLiteDatabase = {

/**
 * @method MoveDatabaseToMemory
 */
MoveDatabaseToMemory : function () {},

/**
 * @method GetLibVersionNumber
 * @return A value converted from C/C++ "int"
 */
GetLibVersionNumber : function () {},

/**
 * @method InterruptDatabaseOperation
 */
InterruptDatabaseOperation : function () {},

/**
 * @method ActivateProfiling
 */
ActivateProfiling : function () {},

/**
 * @method ActivateTracing
 */
ActivateTracing : function () {},

/**
 * @method GetLastInsertRowId
 * @return A value converted from C/C++ "long long"
 */
GetLastInsertRowId : function () {},

/**
 * @method GetAutoCommit
 * @return A value converted from C/C++ "int"
 */
GetAutoCommit : function () {},

/**
 * @method GetMemoryUsage
 * @return A value converted from C/C++ "long long"
 */
GetMemoryUsage : function () {},

/**
 * @method GetMemoryHighwaterMark
 * @return A value converted from C/C++ "long long"
 */
GetMemoryHighwaterMark : function () {},

/**
 * @method GetDatabaseChanges
 * @return A value converted from C/C++ "int"
 */
GetDatabaseChanges : function () {},

/**
 * @method GetTotalDatabaseChanges
 * @return A value converted from C/C++ "int"
 */
GetTotalDatabaseChanges : function () {},

/**
 * @method GetDatabaseHandle
 * @return A value converted from C/C++ "sqlite3*"
 */
GetDatabaseHandle : function () {},

/**
 * @method IsDatabaseReadOnly
 * @return A value converted from C/C++ "bool"
 */
IsDatabaseReadOnly : function () {},

/**
 * @method Close
 */
Close : function () {},

/**
 * @method SetSoftHeapLimit
 * @param {int}
 */
SetSoftHeapLimit : function () {},

};

/**
 * @class SQLiteStatement
 */
kompex.SQLiteStatement = {

/**
 * @method BindDouble
 * @param {int}
 * @param {double}
 */
BindDouble : function () {},

/**
 * @method GetDataCount
 * @return A value converted from C/C++ "int"
 */
GetDataCount : function () {},

/**
 * @method BindZeroBlob
 * @param {int}
 * @param {int}
 */
BindZeroBlob : function () {},

/**
 * @method BindBlob
 * @param {int}
 * @param {const void*}
 * @param {int}
 */
BindBlob : function () {},

/**
 * @method FetchRow
 * @return A value converted from C/C++ "bool"
 */
FetchRow : function () {},

/**
 * @method BindInt
 * @param {int}
 * @param {int}
 */
BindInt : function () {},

/**
 * @method GetTableColumnMetadata
 * @param {std::string}
 * @param {std::string}
 */
GetTableColumnMetadata : function () {},

/**
 * @method BeginTransaction
 */
BeginTransaction : function () {},

/**
 * @method BindInt64
 * @param {int}
 * @param {long long}
 */
BindInt64 : function () {},

/**
 * @method BindNull
 * @param {int}
 */
BindNull : function () {},

/**
 * @method Reset
 */
Reset : function () {},

/**
 * @method Execute
 */
Execute : function () {},

/**
 * @method BindBool
 * @param {int}
 * @param {bool}
 */
BindBool : function () {},

/**
 * @method GetNumberOfRows
 * @return A value converted from C/C++ "unsigned int"
 */
GetNumberOfRows : function () {},

/**
 * @method RollbackTransaction
 */
RollbackTransaction : function () {},

/**
 * @method BindString
 * @param {int}
 * @param {std::string}
 */
BindString : function () {},

/**
 * @method FreeQuery
 */
FreeQuery : function () {},

/**
 * @method BindString16
 * @param {int}
 * @param {const wchar_t*}
 */
BindString16 : function () {},

/**
 * @method ExecuteAndFree
 */
ExecuteAndFree : function () {},

/**
 * @method GetColumnCount
 * @return A value converted from C/C++ "int"
 */
GetColumnCount : function () {},

/**
 * @method ClearBindings
 */
ClearBindings : function () {},

/**
 * @method GetTable
 * @param {std::string}
 * @param {unsigned short}
 */
GetTable : function () {},

/**
 * @method CommitTransaction
 */
CommitTransaction : function () {},

};
