ANDROID_PATH=./android
SUBMODULE_PATH=./submodules/android-store/SoomlaAndroidStore

PROJECT_PROPERTIES_FILE=project.properties
LOCAL_PROPERTIES_FILE=local.properties

if [ -z "$1" ]
then
  echo "ERROR: please, provide target as a first param"
  exit 1
fi

TARGET=$1

if [ ! -e "$SUBMODULE_PATH/$PROJECT_PROPERTIES_FILE" ]
then
  echo "generate properties for submodule"
  echo "android.library=true" > "$SUBMODULE_PATH/$PROJECT_PROPERTIES_FILE"
fi

android update project -p $ANDROID_PATH -t $TARGET
android update project -p $SUBMODULE_PATH -t $TARGET

