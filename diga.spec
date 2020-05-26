
Name:		diga
Version:	1.0.0
Release:	fc32
Summary:	Speech Synthesis CLI tool
License:	LGPLv2+
Group:		Applications/Multimedia
Source:     diga-%{version}.tar.gz
URL:		https://github.com/rramirezacosta


Requires: speech-dispatcher libstdc++ glib2 libtool-ltdl pcre glibc-devel

%description

%global debug_package %{nil}

%prep
%setup -q #unpack tarball

%build

%install
cp -rfa * %{buildroot}

%files
%defattr(-, root, root, -)
/usr/bin/diga
/usr/bin/say

%post

%preun

%postun


