#include <crtdbg.h>

////   /!\  NE FONCTIONNE QUE SOUS VISUAL C++  /!\
///Pour exploiter ce detecteur de fuites memoires, il suffit d'ajouter l'include ci-dessous dans le(s) fichier(s) ou vous souhaitez rechercher des evetuelles fuites
///et d'inserer a un moment du programme la fonction ci-apres
///   #include "leaks_tracker.h"
///   	_CrtDumpMemoryLeaks();

#ifdef _DEBUG
   #define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
   #define DEBUG_CLIENTBLOCK
#endif


#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif