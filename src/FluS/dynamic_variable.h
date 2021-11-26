/**
 * @file dynamic_variable.h
 * @author Tal Rubin (trubin@princeton.edu)
 * @brief A state data structure
 * @version 0.1
 * @date 2021-11-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#ifndef FLUS_DY_VAR_H_
#define FLUS_DY_VAR_H_

#include <valarray>
#include <array>
#include <cstddef>


class Dynamic_Variable {
  public:
  Dynamic_Variable(std::size_t num_ele, std::size_t num_fields, std::size_t num_dg_dof);
  Dynamic_Variable(std::size_t num_ele, std::size_t num_fields);

  Dynamic_Variable(std::array<std::size_t, 3> dim);

 // Dynamic_Variable (const Dynamic_Variable &DV);


  std::array<std::size_t, 3> dim_;
  std::valarray<double> data_;

  /**
   * @brief Access an element (non-iterable, read / write)
   * 
   * @param ele_number 
   * @return std::slice_array<double> 
   */

  inline std::slice_array<double> element (std::size_t ele_number) {
    return data_[std::slice(ele_number * (dim_[1]*dim_[2]),(dim_[1]*dim_[2]),1)];
  };

  /**
   * @brief Get a (read only) iterable element data
   * 
   * @param ele_number 
   * @return std::valarray<double> 
   */
  inline std::valarray<double> get_element (std::size_t ele_number) const {
    return data_[std::slice(ele_number * (dim_[1]*dim_[2]),(dim_[1]*dim_[2]),1)];
  } ;
}; 




#endif  // FLUS_DY_VAR_H_