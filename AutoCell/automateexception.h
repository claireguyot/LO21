#ifndef AUTOMATEEXCEPTION_H
#define AUTOMATEEXCEPTION_H

/*!
 * \file automateexception.h
 * \brief Fichier entête contenant la classe AutomateException.
 */

/*!
 * \class AutomateException : public std::exception
 * \brief Classe de base des exceptions liées au projet qui est utilisée en cas d'erreur.
 *
 * Cette classe instancie toutes les erreurs provoquées par le code en attribuant une chaîne de caractères décrivant l'erreur en question. Elle hérite de la class \a exception de la blibliothèque standard \a std. Il est donc possible d'utiliser les fonctions disponibles pour cette dernière dans notre classe \a AutomateException.
 */

/*!
 * \var std::string info
 * \brief Attribut de la classe AutomateException.
 *
 * Cet attribut est de type string afin de recevoir un string. En effet, il permet de stocker la description de l'erreur lorsque AutomateException est appelée et qu'une nouvelle instance de cette classe est créé.
 * Il est privé afin de respecter le principe d'encapsulation et d'empêcher la modification de la structure de données par l'utilisateur. Ainsi, il est uniquement accessible au travers des méthodes de la classe.
 */

/*!
 * \fn AutomateException(const std::string& message) throw()
 * \brief Constructeur de la classe AutomateException.
 * \param message Ce paramètre permet d'initialiser l'attribut \a info avec une chaîne de caractère passée en argument lors de l'appel du constructeur.
 *
 * Ce constructeur est appelé à l'aide de l'instruction \a throw lorsqu'il y a une erreur.
 * \a Ex: dans le fichier "cellularautomata.cpp"
 * < em>if (m_depart==nullptr) throw AutomateException("etat depart indefini");< /em>
 * La fonction \a throw() issue de la classe \a exception permet d'éviter les boucles d'erreurs liées à l'initialisation de l'attribut < em>info< /em> avec une chaîne non conforme.
 */

 /*!
 * \fn ~AutomateException()
 * \brief Destructeur de la classe AutomateException.
 *
 * Ce destructeur est appelé lors de la destruction d'un objet de la classe \a AutomateException. Les attributs de la classe étant automatiques, il n'est pas nécessaire de désallouer la mémoire.
 */

/*!
 * \fn char const* what() const throw()
 * \brief Accesseur en lecture de l'attribut \a info de la classe AutomateException.
 *
 * Cet accesseur permet d'accéder en lecture à l'attribut privé \a info, en renvoyant un pointeur \a const de celui-ci. Cette méthode ne modifie par l'attribut, c'est pourquoi elle est \a const.
 * La fonction \a c_str() de la blibliothèque standard retourne un tableau contenant la même séquence de caractères composant \a info en ajoutant < em>"\0"< /em> à la fin.
 * La fonction \a throw() issue de la classe \a exception permet d'éviter les boucles d'erreurs liées à ce que renvoie < em>info.c_str()< /em>.
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

