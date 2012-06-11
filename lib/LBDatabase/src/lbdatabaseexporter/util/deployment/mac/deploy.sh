PWD=$1
OUT_PWD=$2
DEPLOY_DIR=$3
ICON=$4
TARGET=$5
APPCASTURL=$6

VERSION=`cd $PWD && /usr/local/git/bin/git describe --tags`

macdeployqt $OUT_PWD/$TARGET.app
cp $ICON $OUT_PWD/$TARGET.app/Contents/Resources/$TARGET.icns
sed 's/\[TARGET]/'$TARGET'/g' $PWD/../util/deployment/mac/Info.plist > $OUT_PWD/$TARGET.app/Contents/Info.plist.tmp
sed 's/\[VERSION\]/'$VERSION'/g' $OUT_PWD/$TARGET.app/Contents/Info.plist.tmp > $OUT_PWD/$TARGET.app/Contents/Info.plist
rm $OUT_PWD/$TARGET.app/Contents/Info.plist.tmp
cp $PWD/../util/deployment/mac/dsa_pub.pem $OUT_PWD/$TARGET.app/Contents/Resources/
cp -R $OUT_PWD/$TARGET.app $DEPLOY_DIR
cp $PWD/../util/deployment/mac/AppCast_mac.xml $DEPLOY_DIR/AppCast.tmp.xml
sed 's/\[VERSION\]/'$VERSION'/g' $DEPLOY_DIR/AppCast.tmp.xml > $DEPLOY_DIR/AppCast.tmp2.xml
cp $PWD/${TARGET}_*.qm $OUT_PWD/${TARGET}.app/Contents/Resources/

cd $OUT_PWD
zip -q $DEPLOY_DIR/${TARGET}.zip -r $TARGET.app
cd -

DSASIGNATURE=`ruby $PWD/../util/deployment/mac/sign_update.rb $DEPLOY_DIR/${TARGET}.zip ~/.ssh/dsa_priv.pem`
sed 's#\[DSASIGNATURE\]#'$DSASIGNATURE'#g' $DEPLOY_DIR/AppCast.tmp2.xml > $DEPLOY_DIR/AppCast.tmp3.xml

sed 's#\[DATE\]#'"`date`"'#g' $DEPLOY_DIR/AppCast.tmp3.xml > $DEPLOY_DIR/AppCast.tmp4.xml
sed 's#\[LENGTH]#'"`du $DEPLOY_DIR/${TARGET}.zip | sed 's/\([0-9]*\)\(.*\)/\1/'`"'#g' $DEPLOY_DIR/AppCast.tmp4.xml > $DEPLOY_DIR/AppCast.tmp5.xml
sed 's#\[TARGET]#'$TARGET'#g' $DEPLOY_DIR/AppCast.tmp5.xml > $DEPLOY_DIR/AppCast.tmp6.xml
sed 's#\[APPCASTURL]#'$APPCASTURL'#g' $DEPLOY_DIR/AppCast.tmp6.xml > $DEPLOY_DIR/AppCast_mac.xml

rm $DEPLOY_DIR/AppCast.tmp*.xml

cp $PWD/../util/deployment/mac/rnotes_mac.html $DEPLOY_DIR
cp $PWD/../util/deployment/rnotes.css $DEPLOY_DIR
