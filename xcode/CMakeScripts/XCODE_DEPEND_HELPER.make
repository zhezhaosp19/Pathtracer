# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.CGL.Debug:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/Debug/libCGL.a:
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/Debug/libCGL.a


PostBuild.glew.Debug:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/Debug/libglew.a:
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/Debug/libglew.a


PostBuild.glfw.Debug:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/Debug/libglfw3.a:
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/Debug/libglfw3.a


PostBuild.pathtracer.Debug:
PostBuild.CGL.Debug: /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/Debug/pathtracer
PostBuild.glew.Debug: /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/Debug/pathtracer
PostBuild.glfw.Debug: /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/Debug/pathtracer
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/Debug/pathtracer:\
	/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/Debug/libCGL.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/usr/local/lib/libfreetype.dylib\
	/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/Debug/libglew.a\
	/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/Debug/libglfw3.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/Debug/pathtracer


PostBuild.CGL.Release:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/Release/libCGL.a:
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/Release/libCGL.a


PostBuild.glew.Release:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/Release/libglew.a:
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/Release/libglew.a


PostBuild.glfw.Release:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/Release/libglfw3.a:
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/Release/libglfw3.a


PostBuild.pathtracer.Release:
PostBuild.CGL.Release: /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/Release/pathtracer
PostBuild.glew.Release: /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/Release/pathtracer
PostBuild.glfw.Release: /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/Release/pathtracer
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/Release/pathtracer:\
	/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/Release/libCGL.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/usr/local/lib/libfreetype.dylib\
	/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/Release/libglew.a\
	/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/Release/libglfw3.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/Release/pathtracer


PostBuild.CGL.MinSizeRel:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/MinSizeRel/libCGL.a:
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/MinSizeRel/libCGL.a


PostBuild.glew.MinSizeRel:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/MinSizeRel/libglew.a:
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/MinSizeRel/libglew.a


PostBuild.glfw.MinSizeRel:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/MinSizeRel/libglfw3.a:
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/MinSizeRel/libglfw3.a


PostBuild.pathtracer.MinSizeRel:
PostBuild.CGL.MinSizeRel: /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/MinSizeRel/pathtracer
PostBuild.glew.MinSizeRel: /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/MinSizeRel/pathtracer
PostBuild.glfw.MinSizeRel: /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/MinSizeRel/pathtracer
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/MinSizeRel/pathtracer:\
	/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/MinSizeRel/libCGL.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/usr/local/lib/libfreetype.dylib\
	/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/MinSizeRel/libglew.a\
	/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/MinSizeRel/libglfw3.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/MinSizeRel/pathtracer


PostBuild.CGL.RelWithDebInfo:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/RelWithDebInfo/libCGL.a:
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/RelWithDebInfo/libCGL.a


PostBuild.glew.RelWithDebInfo:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/RelWithDebInfo/libglew.a:
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/RelWithDebInfo/libglew.a


PostBuild.glfw.RelWithDebInfo:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/RelWithDebInfo/libglfw3.a:
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/RelWithDebInfo/libglfw3.a


PostBuild.pathtracer.RelWithDebInfo:
PostBuild.CGL.RelWithDebInfo: /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/RelWithDebInfo/pathtracer
PostBuild.glew.RelWithDebInfo: /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/RelWithDebInfo/pathtracer
PostBuild.glfw.RelWithDebInfo: /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/RelWithDebInfo/pathtracer
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/RelWithDebInfo/pathtracer:\
	/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/RelWithDebInfo/libCGL.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/usr/local/lib/libfreetype.dylib\
	/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/RelWithDebInfo/libglew.a\
	/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/RelWithDebInfo/libglfw3.a\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd\
	/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd
	/bin/rm -f /Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/RelWithDebInfo/pathtracer




# For each target create a dummy ruleso the target does not have to exist
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/OpenGL.framework/OpenGL.tbd:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/Debug/libCGL.a:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/MinSizeRel/libCGL.a:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/RelWithDebInfo/libCGL.a:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/Release/libCGL.a:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/Debug/libglew.a:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/MinSizeRel/libglew.a:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/RelWithDebInfo/libglew.a:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glew/Release/libglew.a:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/Debug/libglfw3.a:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/MinSizeRel/libglfw3.a:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/RelWithDebInfo/libglfw3.a:
/Users/Emma/Documents/UCB/cs284/p3-1-pathtracer-sp20-zhezhaosp19/xcode/CGL/deps/glfw/src/Release/libglfw3.a:
/usr/local/lib/libfreetype.dylib:
