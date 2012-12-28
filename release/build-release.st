| proxyConfig |
"Configure proxy settings from proxy.config file"
(FileDirectory default fileExists: 'proxy.config')
	ifTrue: [[proxyConfig := ((FileDirectory default
					directoryNamed: '..')
					directoryNamed: '..')
					fileNamed: 'proxy.config'.
		HTTPSocket 
			useProxyServerNamed: ((proxyConfig upTo: $:) 
				ifNotEmpty: [:s | s]
				ifEmpty: [nil])
			port: (proxyConfig upToEnd ifNotEmpty: [:s | s] ifEmpty: [80])]
				ensure: [proxyConfig close]]
	ifFalse: [
		HTTPSocket
			useProxyServerNamed: nil
			port: nil].
		
"Set author initials now to avoid waiting for PE to be downloaded and installed"
Utilities setAuthorInitials: 'Richo'.

"Install latest version of all Physical Etoys packages"
(Installer ss project: 'PhysicalEtoys') install: 'PhysicalEtoys-'.
(Installer ss project: 'CTranslator') install: 'CTranslator-'.
(Installer ss project: 'Arduino') install: 'Arduino-Core-'.
(Installer ss project: 'Arduino') install: 'Arduino-Etoys-'.
(Installer ss project: 'Arduino') install: 'Arduino-Compiler-'.
(Installer ss project: 'Arduino') install: 'Arduino-EtoysCompiler-'.
(Installer ss project: 'SqueakNxt') install: 'SqueakNxt-Core-'.
(Installer ss project: 'SqueakNxt') install: 'SqueakNxt-Etoys-'.
(Installer ss project: 'SqueakNxt') install: 'SqueakNxt-Compiler-'.
(Installer ss project: 'SqueakNxt') install: 'SqueakNxt-EtoysCompiler-'.
(Installer ss project: 'DuinoBot') install: 'DuinoBot-Core-'.
(Installer ss project: 'DuinoBot') install: 'DuinoBot-Etoys-'.
(Installer ss project: 'DuinoBot') install: 'DuinoBot-Compiler-'.
(Installer ss project: 'DuinoBot') install: 'DuinoBot-EtoysCompiler-'.

"Make release"
(Smalltalk at: #PEReleaseBuilder) makeRelease.
