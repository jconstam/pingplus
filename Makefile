ROOT_PATH=$(shell pwd)
PROJ_NAME=pingplus

SOURCE_PATH=${ROOT_PATH}/src
BUILD_PATH=${ROOT_PATH}/build

OUTPUT_PATH_MAIN=${BUILD_PATH}/${PROJ_NAME}

.PHONY: build
build:
	mkdir -p ${OUTPUT_PATH_MAIN} 
	cd ${OUTPUT_PATH_MAIN} \
		&& cmake ${SOURCE_PATH} \
			-DMAIN_PROJECT_NAME:STRING=${PROJ_NAME} \
		&& $(MAKE) $(MAKEFLAGS)
	
.PHONY: clean
clean:
	rm -rf ${BUILD_PATH}