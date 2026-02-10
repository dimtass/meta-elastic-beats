DESCRIPTION = "Compile Elastic metricbeat."

require elastic-beats.inc

GO_PACKAGE = "metricbeat"

do_install:append(){

    install -d ${D}/${sysconfdir}/${GO_PACKAGE}/modules.d
    cp -r ${WORKDIR}/${PN}-${PV}/src/${GO_WORKDIR}/modules.d/ ${D}/${sysconfdir}/${GO_PACKAGE}/

    install -d ${D}/${datadir}/${GO_PACKAGE}/
    cp -r ${WORKDIR}/${PN}-${PV}/src/${GO_WORKDIR}/module ${D}/${datadir}/${GO_PACKAGE}/
}

FILES:${PN} += " ${sysconfdir}/${GO_PACKAGE} \
        ${datadir}/${GO_PACKAGE}/ \
        "