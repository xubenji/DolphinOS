-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA256

Format: 3.0 (quilt)
Source: cockpit
Binary: cockpit, cockpit-bridge, cockpit-dashboard, cockpit-doc, cockpit-docker, cockpit-machines, cockpit-networkmanager, cockpit-pcp, cockpit-packagekit, cockpit-storaged, cockpit-system, cockpit-tests, cockpit-ws
Architecture: any all
Version: 196-1~ubuntu18.04.1
Maintainer: Utopia Maintenance Team <pkg-utopia-maintainers@lists.alioth.debian.org>
Uploaders: Michael Biebl <biebl@debian.org>, Martin Pitt <mpitt@debian.org>,
Homepage: https://cockpit-project.org/
Standards-Version: 4.3.0
Vcs-Browser: https://salsa.debian.org/utopia-team/cockpit
Vcs-Git: https://salsa.debian.org/utopia-team/cockpit.git
Testsuite: autopkgtest
Testsuite-Triggers: curl
Build-Depends: debhelper (>= 10), dpkg-dev (>= 1.17.14), intltool, libssh-dev, zlib1g-dev, libkrb5-dev, libxslt1-dev, libglib2.0-dev, libsystemd-dev, libpolkit-agent-1-dev, libpcp3-dev, libjson-glib-dev, libpam0g-dev, libpcp-import1-dev, libpcp-pmda3-dev, systemd, xsltproc, xmlto, docbook-xsl, glib-networking, openssh-client <!nocheck>, python3
Package-List:
 cockpit deb admin optional arch=all
 cockpit-bridge deb admin optional arch=any
 cockpit-dashboard deb admin optional arch=all
 cockpit-doc deb doc optional arch=all
 cockpit-docker deb admin optional arch=all
 cockpit-machines deb admin optional arch=all
 cockpit-networkmanager deb admin optional arch=all
 cockpit-packagekit deb admin optional arch=all
 cockpit-pcp deb admin optional arch=any
 cockpit-storaged deb admin optional arch=all
 cockpit-system deb admin optional arch=all
 cockpit-tests deb admin optional arch=any
 cockpit-ws deb admin optional arch=any
Checksums-Sha1:
 b15bce22d7aaf99e60d0fb12678b5298c49bc2a6 13071924 cockpit_196.orig.tar.xz
 28f6bf3f71101f82abdeaddd35c280ae56746e6b 15440 cockpit_196-1~ubuntu18.04.1.debian.tar.xz
Checksums-Sha256:
 c625562fd5b6296d91ea7550ac05dbe16eaf8f7e60536c2d61119bd4445ae1d2 13071924 cockpit_196.orig.tar.xz
 fe0170fbd167ad1d7b57d5b8e233fb180a50f07070f8605acb9d13b451187ce0 15440 cockpit_196-1~ubuntu18.04.1.debian.tar.xz
Files:
 8369c2d403996ae55cd92b6c65ccf87d 13071924 cockpit_196.orig.tar.xz
 3e53b6cb505bd545dbc82afe6a6169aa 15440 cockpit_196-1~ubuntu18.04.1.debian.tar.xz

-----BEGIN PGP SIGNATURE-----

iQIzBAEBCAAdFiEExkOAo1eT0DvBz+1oxrkYDUvYt64FAl0GrSYACgkQxrkYDUvY
t67r6w/+I2XmGiB0shkGsj0E6yCBswcRuhkWr/20u8jjGmrSxdQdTq9gXhcoj63M
ygqguZ1jpqFIzhQDfks09SPs3T1Q4RMyhjIbw/e2MXKbHdNPs4KmTTq9jWzRy+hx
KHGuY4TtEDLSbO5u3BOQdWqBNHFFqiU50KEwgpT6X4obbUCTu+hkvWTM3gbswfq4
m7t+N7fbWJ+F9nPvATSWYDqN86QDkTX2e1PMDdn66IRLPskFwo2oDlFuNuTZxOgG
g8NmntmCvwn44gtR5L805iN7Npx8jteMyq0MGo+nmET/nawisZsqvw9iJFqd64r8
tFf9+qWYMm2D2+hS3n71pe+F/PagP10iLXfCiWgcno7xQXsXIoXk2k6UY/zeaPf0
H0WDXW5nete0vROvLyVS66Eu1qS/jY+m+lEDho068ZkCQnl7iChAfVIhocEh437n
woKLSiqcym8NosP3l7WIotK6XBSDj9b/872HBngzbGlAFJO0taKeruisCX6vyaVL
V8lk2dgdhF88497E6xk0YI3Sv3elU9rfOFxfxDCjTQn6FfP3t15PWtMEfdfLjFaw
GcHOjJERw5nlaOPqCEjYc43tD8Zkom2oXXI0j7TXrMWBCQr5aZ58vfyNVSIAoQJi
yRyTZJz7adl17YiWdWxbJPTX1aWTl+w+YDyYdjt71gvS4BCrkbA=
=w0Ie
-----END PGP SIGNATURE-----
