| proxyConfig |
"Configure proxy settings from proxy.config file"
[proxyConfig := ((FileDirectory default
					directoryNamed: '..')
					directoryNamed: '..')
					fileNamed: 'proxy.config'.
HTTPSocket 
	useProxyServerNamed: ((proxyConfig upTo: $:) ifNotEmpty: [:s | s] ifEmpty: [nil])
	port: (proxyConfig upToEnd ifNotEmpty: [:s | s] ifEmpty: [80])]
		ensure: [proxyConfig close].
		
"Set author initials now to avoid waiting for PE to be downloaded and installed"
Utilities setAuthorInitials: 'Richo'.

"Install latest version of all Physical Etoys packages"
(Installer ss project: 'PhysicalEtoys') install: 'PhysicalEtoys-'.
(Installer ss project: 'CTranslator') install: 'CTranslator-'.
(Installer ss project: 'Arduino') install: 'Arduino-Core-'.
(Installer ss project: 'Arduino') install: 'Arduino-Compiler-'.
(Installer ss project: 'Arduino') install: 'Arduino-Etoys-'.
(Installer ss project: 'SqueakNxt') install: 'SqueakNxt-Core-'.
(Installer ss project: 'SqueakNxt') install: 'SqueakNxt-Etoys-'.
(Installer ss project: 'ControlLab') install: 'ControlLab-'.
(Installer ss project: 'ParallelPort') install: 'ParallelPort-'.
(Installer ss project: 'SqueakWiimote') install: 'Wiimote-'.
(Installer ss project: 'DuinoBot') install: 'DuinoBot-'.

"Turn on 'kid mode'"
Preferences enable:#eToyFriendly.

"Remove development windows"
(World submorphs
  select: [:e | e isMemberOf: SystemWindow])
  do: [:e | e delete].

"Save image and Quit"
"World 
	addAlarm: #value 
	withArguments: #() 
	for: [SmalltalkImage current snapshot: true andQuit: true]
	at: Time millisecondClockValue + 2000"
SmalltalkImage current snapshot: true andQuit: true.
