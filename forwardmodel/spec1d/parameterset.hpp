#pragma once
#ifndef parameterset_hpp
#define parameterset_hpp

#include <array>

#include "encodedecode.hpp"

template
<
  typename real,
  size_t set_size
>
class ParameterSet : public std::array<real, set_size> {
public:

  static constexpr size_t NPARAMETERS = set_size;

  ParameterSet()
  {
  }

  virtual ~ParameterSet()
  {
  }

  virtual real rho(real depth) const = 0;
  
  virtual real A(real depth) const = 0;
  
  virtual real C(real depth) const = 0;
  
  virtual real F(real depth) const = 0;
  
  virtual real L(real depth) const = 0;
  
  virtual real N(real depth) const = 0;

  virtual real drho(size_t i, real depth) const = 0;
  
  virtual real dA(size_t i, real depth) const = 0;
  
  virtual real dC(size_t i, real depth) const = 0;
  
  virtual real dF(size_t i, real depth) const = 0;
  
  virtual real dL(size_t i, real depth) const = 0;
  
  virtual real dN(size_t i, real depth) const = 0;
  
  virtual bool read(FILE *fp)
  {
    for (auto &r : *this) {
      double t;
      if (fscanf(fp, "%lf", &t) != 1) {
	return false;
      }
      r = t;      
    }

    return true;
  }

  virtual bool read_parameter(int k, FILE *fp)
  {
    if (k < 0 || k >= (int)set_size) {
      return false;;
    }

    double t;

    if (fscanf(fp, "%lf", &t) != 1) {
      return false;
    }

    (*this)[k] = t;
    return true;
  }

  virtual bool write(FILE *fp) const
  {
    for (auto &r : *this) {
      fprintf(fp, "%15.9f ", (double)r);
    }
    fprintf(fp, "\n");
    return true;
  }

  virtual bool write_parameter(int k, FILE *fp) const
  {
    if (k < 0 || k >= (int)set_size) {
      return false;;
    }

    fprintf(fp, "%15.9f", (double)((*this)[k]));
    return true;
  }

  virtual size_t encode_size() const
  {
    return sizeof(real) * set_size;
  }

  virtual size_t encode_parameter_size(int k) const
  {
    return sizeof(real);
  }

  int encode(char *buffer, int &buffer_offset, int buffer_size) const
  {
    for (auto &r : *this) {
      if (::encode<real>(r, buffer, buffer_offset, buffer_size) < 0) {
	return -1;
      }
    }

    return encode_size();
  }

  int encode_parameter(int k, char *buffer, int &buffer_offset, int buffer_size) const
  {
    if (k < 0 || k >= (int)set_size) {
      return -1;
    }
    
    if (::encode<real>((*this)[k], buffer, buffer_offset, buffer_size) < 0) {
      return -1;
    }

    return encode_parameter_size(k);
  }

  int decode(const char *buffer, int &buffer_offset, int buffer_size)
  {
    for (auto &r : *this) {
      if (::decode<real>(r, buffer, buffer_offset, buffer_size) < 0) {
	return -1;
      }
    }

    return encode_size();
  }
    
  int decode_parameter(int k, const char *buffer, int &buffer_offset, int buffer_size)
  {
    if (k < 0 || k >= (int)set_size) {
      return -1;
    }
    
    if (::decode<real>((*this)[k], buffer, buffer_offset, buffer_size) < 0) {
      return -1;
    }

    return encode_parameter_size(k);
  }
};

#endif // parameterset_hpp
