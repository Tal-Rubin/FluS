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
 * and \f$E =  \frac{1}{2}\rho(u^2+v^2+w^2)+\frac{p}{(\gamma-1)}\f$
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
    Ers(std::array<double, 5> left, std::array<double, 5> right, double gamma);
    //! ERS destructor
    ~Ers();
    //! Exact solution for the Euler equations at (x,t)
    std::array<double,5> W(double t, double x);
    std::array<double,5> U(double t, double x);

  protected:
    //! State std::array containing \f$(\rho, u, v, w, p)\f$ for the left initial state 
    std::array<std::array<double, 5>,2> state_;
    /**
     * @brief Ratio of specific heats
     * 
     * \f$\gamma  = 5/3\f$ for a monoatomic gas, 
     * \f$\gamma  = 7/5\f$ for a duoatomic gas.
     */
    double gamma_;

    double G1_,G2_;
    //! Sound speed array (left, right)
    std::array<double,2> a_;
    //! Shock (true) or Rarefaction (false)
    std::array<bool,2> SR_;
    //! funciton to  calculate sound speed
    void sound_speed();
    //! particle velocity in star region
    double u_star_;
    //! pressure in star region
    double p_star_;
    //! density in star region (left, right)
    std::array<double,2> rho_star_;
    //! shock speed / head / tail of rarefaction wave  (left (head, tail), right (head, tail))
    std::array<std::array<double,2>,2> S_;

    void find_pu_star();
    double guess_p_star();
    std::array<double,3> functor_p_star(double p);
    void density_speed();


};

#endif // ERS_
