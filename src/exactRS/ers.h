/**
 * @file
 * Header for the Exact Riemann Solver class.
 * 
 * Implementation based on Toro, Eleuterio F. Riemann solvers and numerical methods for fluid dynamics: a practical introduction. Springer, 1999.
 * \copyright Copyright (c) 2021 Tal Rubin Distributed under MIT License.
*/

#ifndef ERS_
#define ERS_

#include <array>
/*! \class Ers
 * \brief Class for exact solution of Euler equations in 1 dimension:
 * \f[U +\nabla \cdot F(U)=0 \f]
 * with \f$U = (\rho, \rho v, \rho u, \rho w, E)^T\f$ and \f$F=(\rho u, \rho u^2 + p, \rho u v, \rho u w, u (E+p))^T\f$
 * and \f$E = \rho (\frac{1}{2}(u^2+v^2+w^2)+\frac{p}{(\gamma-1)\rho})\f$
 */
class Ers {
  public:
    /**
     * @brief Construct a new Ers object
     * 
     * @param left State std::array for the primitive quantities for the negative half-line
     * @param right State std::array for the primitive quantities for the positive half-line
     * @param gamma Isentropic espansion ratio / ratio of specific heats
     */
    Ers(std::array<double, 5> left, std::array<double, 5> right, double gamma = 5./3);
    //! ERS destructor
    ~Ers();
    //! Exact solution for the Euler equations at (x,t)
    double sol(double t, double x);

  protected:
    //! State std::array containing \f$(\rho, u, v, w, p)\f$ for the left initial state 
    std::array<double, 5> left_;
    //! State std::array containing \f$(\rho, u, v, w, p)\f$ for the right initial state
    std::array<double, 5> right_;
    /**
     * @brief Ratio of specific heats
     * 
     * \f$\gamma  = 5/3\f$ for a monoatomic gas, 
     * \f$\gamma  = 7/5\f$ for a duoatomic gas.
     */
    double gamma_;
    //! Sound speed array (left, right)
    std::array<double,2> a_;
    //! funciton to  calculate sound speed
    double sound_speed(std::array<double, 5> state);
    //! particle velocity in star region
    double u_star_;
    //! pressure in star region
    double p_star_;

    void find_pu_star();
    double guess_p_star();

};

#endif // ERS_
