.PHONY: FORCE
all: FORCE
	$(MAKE) -C .. ludirium_qt test_ludirium_qt
clean: FORCE
	$(MAKE) -C .. ludirium_qt_clean test_ludirium_qt_clean
check: FORCE
	$(MAKE) -C .. test_ludirium_qt_check
ludirium-qt ludirium-qt.exe: FORCE
	 $(MAKE) -C .. ludirium_qt
apk: FORCE
	$(MAKE) -C .. ludirium_qt_apk
