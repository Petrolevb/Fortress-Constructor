#ifndef HPP_DEFINITIONS
#define HPP_DEFINITIONS

enum
{
	ID_NEstPasAtteingable = 0, // N'est pas touchable par la caméra
	ID_EstAtteignable = 1,
	ID_Objet = 1 << 0, // objet atteignable, de base
	ID_Objet_Porte = 1 << 1 // objet porte, id spécifique
};

#endif
