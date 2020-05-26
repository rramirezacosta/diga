diga
=================
*Speech Synthesis CLI tool*

Convert text to audible speech.

Usage
------------------
For english:

```console
[user@localhost ~] $ say "Say hello to my litle friend"

```

For spanish:

```console
[usuario@localhost ~] $ diga "He visto cosas que no creerías"
```


Build
-------------------------
```console
[user@localhost ~] $ cd diga
[user@localhost ~] $ make

options:

*     make binaries        -builds binaries
*     make local-install   -install diga for the current user on ~/.local/bin/ (no root required)
*     make install         -install diga for all users (root required)
*     make rpm             -creates a RPM package

[user@localhost ~] $ make binaries
[user@localhost ~] $ make local-install

```

Install from RPM
-------------------------
There are rpm's available for fedora Workstation. Feel free to build your own package if you're using other OS.

available at: https://github.com/rramirezacosta/diga/releases

```console
[user@localhost ~] $ sudo rpm -i diga-1.0.0-fc32.x86_64.rpm
```







