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

WorldState addDeferredUIMessage: [			
	"Set author initials now to avoid waiting for PE to be downloaded and installed"
	Utilities setAuthorInitials: 'Richo'.
	(Installer ss project: 'PhysicalEtoys') install: 'PhysicalEtoys-'.

	"Make release"
	(Smalltalk at: #PEReleaseBuilder) makeRelease.
]