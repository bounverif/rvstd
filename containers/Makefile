RVSTD_IMAGE_NAME ?= localhost/rvstd
RVSTD_VERSION ?= latest
CONTEXT ?= .
CONTAINER_CACHE_TTL=24h

builder: 
	buildah build \
		-f rvstd-devel/Dockerfile \
		--build-arg RVSTD_IMAGE_NAME=${RVSTD_IMAGE_NAME} \
		--build-arg RVSTD_VERSION=${RVSTD_VERSION} \
		--format oci \
		--layers=true \
		--cache-ttl=${CONTAINER_CACHE_TTL} \
		--target rvstd-builder \
		--tag rvstd:${RVSTD_VERSION}-builder \
	${CONTEXT}

devel: builder
	buildah build \
		-f rvstd-devel/Dockerfile \
		--build-arg RVSTD_IMAGE_NAME=${RVSTD_IMAGE_NAME} \
		--build-arg RVSTD_VERSION=${RVSTD_VERSION} \
		--format oci \
		--layers=true \
		--cache-ttl=${CONTAINER_CACHE_TTL} \
		--target rvstd-devel \
		--tag rvstd:${RVSTD_VERSION}-devel \
	${CONTEXT}
