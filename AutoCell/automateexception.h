#ifndef AUTOMATEEXCEPTION_H
#define AUTOMATEEXCEPTION_H

/*!
 * \file automateexception.h
 * \brief Fichier entete contenant la classe AutomateException.
 */

#include <string>
#include <exception>

/*!
 * \class AutomateException : public std::exception
 * \brief Classe de base des exceptions liees au projet qui est utilisee en cas d'erreur.
 *
 * Cette classe instancie toutes les erreurs provoquees par le code en attribuant une chaine de caracteres decrivant l'erreur en question. Elle herite de la class \a exception de la blibliotheque standard \a std. Il est donc possible d'utiliser les fonctions disponibles pour cette derniere dans notre classe \a AutomateException.
 */
class AutomateException : public std::exception {
public:
        /*!
         * \brief Constructeur de la classe AutomateException.
         * \param message Ce parametre permet d'initialiser l'attribut \a info avec une chaine de caracteres passee en argument lors de l'appel du constructeur.
         *
         * Ce constructeur est appele a l'aide de l'instruction \a throw lorsqu'il y a une erreur.
         * \a Ex: dans le fichier "cellularautomata.cpp"
         * < em>if (m_depart==nullptr) throw AutomateException("etat depart indefini");< /em>
         * La fonction \a throw() issue de la classe \a exception permet d'eviter les boucles d'erreurs liees a l'initialisation de l'attribut < em>info< /em> avec une chaine non conforme.
         */
    AutomateException(const std::string& message) throw() :info(message) {}
        /*!
         * \brief Accesseur en lecture de l'attribut \a info de la classe AutomateException.
         *
         * Cet accesseur permet d'acceder en lecture a l'attribut prive \a info, en renvoyant un pointeur \a const de celui-ci. Cette methode ne modifie par l'attribut, c'est pourquoi elle est \a const.
         * La fonction \a c_str() de la bibliotheque standard retourne un tableau contenant la meme sequence de caracteres composant \a info en ajoutant < em>"\0"< /em> a la fin.
         * La fonction \a throw() issue de la classe \a exception permet d'eviter les boucles d'erreurs liees a ce que renvoie < em>info.c_str()< /em>.
         * La fonction \a what() issue de la classe \a exception permet de s'assurer que la chaine retourner par < em>info.c_str()< /em> se termine avec \a null.
         */
    char const* what() const throw() { return info.c_str(); }
         /*!
         * \brief Destructeur de la classe AutomateException.
         *
         * Ce destructeur est appele lors de la destruction d'un objet de la classe \a AutomateException. Les attributs de la classe etant automatiques, il n'est pas necessaire de desallouer la memoire.
         */
    ~AutomateException() { }
private:
    /*!
     * \brief Attribut de la classe AutomateException.
     *
     * Cet attribut est de type string afin de recevoir un string. En effet, il permet de stocker la description de l'erreur lorsque AutomateException est appelee et qu'une nouvelle instance de cette classe est cree.
     * Il est prive afin de respecter le principe d'encapsulation et d'empecher la modification de la structure de donnees par l'utilisateur. Ainsi, il est uniquement accessible au travers des methodes de la classe.
     */
    std::string info;
};

#endif // AUTOMATEEXCEPTION_H

