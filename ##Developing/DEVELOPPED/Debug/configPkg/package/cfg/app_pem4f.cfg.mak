# invoke SourceDir generated makefile for app.pem4f
app.pem4f: .libraries,app.pem4f
.libraries,app.pem4f: package/cfg/app_pem4f.xdl
	$(MAKE) -f C:\Users\Mohab\workspace_v7_new\ECUS_RTOS_UNDER_DEVELOP/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Mohab\workspace_v7_new\ECUS_RTOS_UNDER_DEVELOP/src/makefile.libs clean

