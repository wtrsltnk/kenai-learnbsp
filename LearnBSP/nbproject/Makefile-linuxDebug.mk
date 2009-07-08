.build-conf:
	@echo Tool collection not found.
	@echo Please specify existing tool collection in project properties
	@exit 1

# Clean Targets
.clean-conf:
	${RM} -r build/linuxDebug
	${RM} dist/linuxDebug//learnbsp.exe

# Subprojects
.clean-subprojects:
