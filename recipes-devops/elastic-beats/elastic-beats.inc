DESCRIPTION = "Compile Elastic Stack Beats."
HOMEPAGE = "https://github.com/elastic/beats"
AUTHOR = "Dimitris Tassopoulos <dimtass@gmail.com>"

inherit go go-mod

S = "${BEATS_S}"

GO_PACKAGE ?= ""

GO_IMPORT = "github.com/elastic/beats"
GO_INSTALL = "${GO_IMPORT}/${GO_PACKAGE}"
BEAT_FOLDER = "${BEATS_S}/src/${GO_INSTALL}"

CGO_CFLAGS += "--sysroot=${STAGING_DIR_TARGET} -I${STAGING_INCDIR}"
CGO_LDFLAGS += "--sysroot=${STAGING_DIR_TARGET} -L${STAGING_LIBDIR}"

LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://LICENSE.txt;md5=00294979737b05a575493ff7b723f25c"

PV = "9.2.0"
SRCBRANCH ?= "9.2"
SRCREV ?= "09b547febe1cc9102a5d3f80ac8fbf68a5fd84f5"

FILESEXTRAPATHS:append = "${THISDIR}/elastic-beats:"

SRC_URI = " \
        git://${GO_IMPORT}.git;protocol=https;branch=${SRCBRANCH} \
        file://${GO_PACKAGE}.yml \
        "

RDEPENDS:${PN} += "bash"

do_configure:append() {
    # Fix missing src directory in whinlatter
    ln -snf ${S} ${S}/src
}

do_compile[network] = "1"

do_compile() {
    cd ${B}/src/${GO_PACKAGE}
    export http_proxy="${http_proxy}"
    export https_proxy="${https_proxy}"
    go build ${GOBUILDFLAGS}
    # This is needed to remove read-only files
    go clean -modcache
    rm -rf src/${GO_IMPORT}/pkg/mod
    find ${B}/pkg -type d -exec chmod 775 {} \;
}

do_install() {
    create_exec_script

    install -d ${D}${bindir}/
    install -m 0755 ${WORKDIR}/${GO_PACKAGE} ${D}${bindir}

    install -d ${D}${datadir}/${GO_PACKAGE}/bin
    install -m 0755 ${B}/src/${GO_PACKAGE}/${GO_PACKAGE} ${D}${datadir}/${GO_PACKAGE}/bin/

    install -d ${D}${sysconfdir}/${GO_PACKAGE}
    install -m 0755 ${BEATS_S}/../${GO_PACKAGE}.yml ${D}${sysconfdir}/${GO_PACKAGE}/${GO_PACKAGE}.yml

    install -d ${D}${localstatedir}/lib/${GO_PACKAGE}
    install -d ${D}${localstatedir}/log/${GO_PACKAGE}

}

create_exec_script() {
    if [ -f ${WORKDIR}/${GO_PACKAGE} ]; then
        rm ${WORKDIR}/${GO_PACKAGE}
    fi
    cat >> "${WORKDIR}/${GO_PACKAGE}" <<EOF
#!/usr/bin/env bash

# Script to run ${GO_PACKAGE} in foreground with the same path settings that
# the init script / systemd unit file would do.

exec ${datadir}/${GO_PACKAGE}/bin/${GO_PACKAGE} \\
  --path.home ${datadir}/${GO_PACKAGE} \\
  --path.config ${sysconfdir}/${GO_PACKAGE} \\
  --path.data ${localstatedir}/lib/${GO_PACKAGE} \\
  --path.logs ${localstatedir}/log/${GO_PACKAGE} \\
  "\$@"

EOF
    chmod +x ${WORKDIR}/${GO_PACKAGE}
}

FILES:${PN} += " \
        ${datadir} \
        ${sysconfdir} \
"
