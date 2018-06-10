#ifndef AUTOMATEEXCEPTION_H
#define AUTOMATEEXCEPTION_H

/*!
 * \file automateexception.h
 * \brief Fichier ent�te contenant la classe AutomateException.
 */

/*!
 * \class AutomateException : public std::exception
 * \brief Classe de base des exceptions li�es au projet qui est utilis�e en cas d'erreur.
 *
 * Cette classe instancie toutes les erreurs provoqu�es par le code en attribuant une cha�ne de caract�res d�crivant l'erreur en question. Elle h�rite de la class \a exception de la bliblioth�que standard \a std. Il est donc possible d'utiliser les fonctions disponibles pour cette derni�re dans notre classe \a AutomateException.
 */

/*!
 * \var std::string info
 * \brief Attribut de la classe AutomateException.
 *
 * Cet attribut est de type string afin de recevoir un string. En effet, il permet de stocker la description de l'erreur lorsque AutomateException est appel�e et qu'une nouvelle instance de cette classe est cr��.
 * Il est priv� afin de respecter le principe d'encapsulation et d'emp�cher la modification de la structure de donn�es par l'utilisateur. Ainsi, il est uniquement accessible au travers des m�thodes de la classe.
 */

/*!
 * \fn AutomateException(const std::string& message) throw()
 * \brief Constructeur de la classe AutomateException.
 * \param message Ce param�tre permet d'initialiser l'attribut \a info avec une cha�ne de caract�re pass�e en argument lors de l'appel du constructeur.
 *
 * Ce constructeur est appel� � l'aide de l'instruction \a throw lorsqu'il y a une erreur.
 * \a Ex: dans le fichier "cellularautomata.cpp"
 * < em>if (m_depart==nullptr) throw AutomateException("etat depart indefini");< /em>
 * La fonction \a throw() issue de la classe \a exception permet d'�viter les boucles d'erreurs li�es � l'initialisation de l'attribut < em>info< /em> avec une cha�ne non conforme.
 */

 /*!
 * \fn ~AutomateException()
 * \brief Destructeur de la classe AutomateException.
 *
 * Ce destructeur est appel� lors de la destruction d'un objet de la classe \a AutomateException. Les attributs de la classe �tant automatiques, il n'est pas n�cessaire de d�sallouer la m�moire.
 */

/*!
 * \fn char const* what() const throw()
 * \brief Accesseur en lecture de l'attribut \a info de la classe AutomateException.
 *
 * Cet accesseur permet d'acc�der en lecture � l'attribut priv� \a info, en renvoyant un pointeur \a const de celui-ci. Cette m�thode ne modifie par l'attribut, c'est pourquoi elle est \a const.
 * La fonction \a c_str() de la bliblioth�que standard retourne un tableau contenant la m�me s�quence de caract�res composant \a info en ajoutant < em>"\0"< /em> � la fin.
 * La fonction \a throw() issue de la classe \a exception permet d'�viter les boucles d'erreurs li�es � ce que renvoie < em>info.c_str()< /em>.
 * La fonction \a what() issue de la classe \a exception permet de s'assurer que la chaine retourner par < em>info.c_str()< /em> se termine avec \a null.
 */

#include <string>
#include <exception>
class AutomateException : public std::exception {
public:
    AutomateException(const std::string& message) throw() :info(message) {}
    char const* what() const throw() { return info.c_str(); }
    ~AutomateException() { }
private:
    std::string info;
};

#endif // AUTOMATEEXCEPTION_H

