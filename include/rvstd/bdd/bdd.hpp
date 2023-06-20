/*
 * Copyright (c) 2023 for portions of the project HermesBDD are held by 
 *   Luigi Capogrosso, 
 *   Luca Geretti, 
 *   Marco Cristani, 
 *   Franco Fummi, and 
 *   Tiziano Villa.
 *
 * Copyright (c) for the project RVSTD are held by Dogan Ulus, 2023.
 */

#ifndef BDD_HPP
#define BDD_HPP

#include <set>
#include <unordered_map>

namespace rvstd {
struct bdd {

    /*!
     * @brief '<bdd>' empty constructor.
     */
    bdd();

    /*!
     * @brief Representation of literal '<v>'.
     * @param v
     */
    bdd(uint32_t v);

    /// Representation of constant 'true'
    static bdd true_;

    /// Representation of constant 'false'
    static bdd false_;

};
}  // namespace rvstd

#endif
