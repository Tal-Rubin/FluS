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
  /**
   * @brief Construct a new Dynamic_Variable object
   * 
   * @param num_ele 
   * @param num_fields 
   * @param num_coeff 
   */
  Dynamic_Variable(std::size_t num_ele, std::size_t num_fields, std::size_t num_coeff);

  /**
   * @brief Construct a new Dynamic_Variable object
   * 
   * @param num_ele 
   * @param num_fields 
   */
  Dynamic_Variable(std::size_t num_ele, std::size_t num_fields);

  /**
   * @brief Construct a new Dynamic_Variable object
   * 
   * @param dim 
   */
  Dynamic_Variable(std::array<std::size_t, 3> dim);

  /// Copy constructor
 // Dynamic_Variable (const Dynamic_Variable &DV);





  /**
   * @brief Access an element (non-iterable, read / write)
   * 
   * @param ele_number 
   * @return std::slice_array<double> 
   */

  inline std::slice_array<double> element (std::size_t ele_number) { 
    return data_[std::slice(ele_number * element_size_, element_size_, 1)];
  };

  /**
   * @brief Get a (read only) iterable element data
   * 
   * @param ele_number 
   * @return std::valarray<double> 
   */
  inline std::valarray<double> get_element (std::size_t ele_number) const {
    return data_[std::slice(ele_number * element_size_, element_size_, 1)];
  };
  
  /**
   * @brief 
   * 
   * @param field_number 
   * @param coeff_number 
   * @return std::slice_array<double> 
   */
  inline std::slice_array<double> field_coeff (std::size_t field_number, std::size_t coeff_number) { 
    return data_[std::slice(field_number * dim_[2] + coeff_number, dim_[0], element_size_)];
  };

  /**
   * @brief Get the field coeff object
   * 
   * @param field_number 
   * @param coeff_number 
   * @return std::valarray<double> 
   */
  inline std::valarray<double> get_field_coeff (std::size_t field_number, std::size_t coeff_number) const {
    return data_[std::slice(field_number * dim_[2] + coeff_number, dim_[0], element_size_)];
  } ;


  /// @brief Getter funciton for the dim_ array
  std::array<std::size_t, 3> dim() const;
  /// Getter funciton for the element size
  std::size_t element_size() const;
  /// Getter funciton for number of coefficinets
  std::size_t coeff_num() const;


  std::valarray<double> data_;
  private:
  std::array<std::size_t, 3> dim_;
  std::size_t element_size_;
}; 




#endif  // FLUS_DY_VAR_H_