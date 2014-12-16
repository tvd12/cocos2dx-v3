--------------------------------------------------
Per compilare ZLib in Eclipse
--------------------------------------------------
- Da "C:\Projects\Software\Vss\Customer Archives\SmartFoxServer 2X\API Client\Cpp\trunk_api\ZLib" eseguire in una shell dos il comando
	make -fwin32/makefile.gcc
  Il risultato della compilazione sono i files libz.a e libz.dll.a nel folder stesso

--------------------------------------------------
Per compilare le API in Eclipse
--------------------------------------------------
- Apripre Eclipse
- Dal menu scegliere File\New\Project
- Dalla dialog di project wizard selezionare "C++ Project" nella sezione "C/C++", quindi premere Next
- Dalla dialog "C++ Project" impostare:
	1) un project name a proprio piacere (ad esempio SmartFoxClientApi)
	2) Rimuovere il flag "Use default location"
	3) Utilizzando il pulsante browse impostare come Location il path "C:\Projects\Software\Vss\Customer Archives\SmartFoxServer 2X\API Client\Cpp\trunk_api"
	4) Selezionare come Project type "Empty project" dalla sezione "Shared library"
	5) Selezionare come Toolchains "Cygwin GCC"
  Quindi premere il pulsante Finish
- Eclipse genera al progetto ed al termine visualizza una dialog per chiedere l'apertura della "C/C++ perspective"
  Rispondere alla dialog premendo il pulsante Yes
- Chiudere la windows di welcome di Eclipse ed accedere alla window di Project Explorer
  Effettuare le seguenti impostazioni:
	
	- Escludere dalla build (premere tasto destro mouse su ogni progetto, quindi dal popup menu scegliere
	  Resource configuration\Exclude from build)

		Deploy
		BoostAsio (nel folder Core)
		SmartFoxClientApi
		Zlib

	


	- Nei project settings, per l'oggetto "Cygwin C++ Compiler" aggiungere nella sezione Preprocessor
	  la defined symbol __USE_W32_SOCKETS

	- Nei project settings, per l'oggetto "Cygwin C++ Compiler" aggiungere nella sezione Preprocessor
	  la defined symbol SMARTFOXCLIENTAPI_EXPORTS

	- Nei project settings, per l'oggetto "Cygwin C++ Compiler" aggiungere nella sezione Includes 
	  l'include path Core/BoostAsio/Unix/ cercando con il browsing su file system

	- Nei project settings, per l'oggetto "Cygwin C++ Compiler" aggiungere nella sezione Preprocessor
	  la defined symbol _WIN32_WINNT=0x0501


	- Nei project settings, per l'oggetto "Cygwin C++ Linker" aggiungere nella sezione Libraries
	  le librerie
		ws2_32
		boost_thread
		boost_system
	   i library search path
		"C:\Projects\Software\Vss\Customer Archives\SmartFoxServer 2X\API Client\Cpp\trunk_api\Core\BoostAsio\Unix\stage\lib"

- Dal menu selezionare Project/Build project per ricompilare tutti i sorgenti


