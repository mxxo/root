// @(#)root/tmva/tmva/test/dnn $Id$
// Author: Simon Pfreundschuh

/*************************************************************************
 * Copyright (C) 2016, Simon Pfreundschuh
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

//////////////////////////////////////////////////////////////////////
// Concrete instantiation of the generic activation function test   //
// for the TCuda implementation.                                    //
//////////////////////////////////////////////////////////////////////

#include <iostream>
#include "TMVA/DNN/Architectures/Cuda.h"
#include "Utility.h"
#include "TestActivationFunctions.h"

using namespace TMVA::DNN;

int main()
{
    using Scalar_t = Double_t;

    std::cout << "Testing Activation Functions:" << std::endl;

    //create dummy tensor to initialize Cuda/Cudnn
    TCudaTensor<Scalar_t> dummy(1, 1);

    double error;

    // Identity.

    error = testIdentity<TCuda<Scalar_t>>(10);
    std::cout << "Testing identity activation:            ";
    std::cout << "maximum relative error = " << error << std::endl;
    if (error > 1e-5)
        return 1;

#if 0 // fix to not use reference arch
    error = testIdentityDerivative<TCuda<Scalar_t>>(10);
    std::cout << "Testing identity activation derivative: ";
    std::cout << "maximum relative error = " << error << std::endl;
    if (error > 1e-5)
        return 1;
#endif

    // ReLU.

  error = testRelu<TCuda<Scalar_t>>(10);
   std::cout << "Testing ReLU activation:                ";
   std::cout << "maximum relative error = " << error << std::endl;
   if (error > 1e-10) {
       std::cout << "Error - RELU activation test failed" << std::endl;
       return 1;
   }

   error = testReluDerivative<TCuda<Scalar_t>>(10);
   std::cout << "Testing ReLU activation derivative:     ";
   std::cout << "maximum relative error = " << error << std::endl;
   if (error > 1e-10) { 
       std::cout << "Error - RELU derivative activation test failed" << std::endl;
       return 1;
   }
   // Sigmoid.

   error = testSigmoid<TCuda<Scalar_t>>(10);
   std::cout << "Testing Sigmoid activation:             ";
   std::cout << "maximum relative error = " << error << std::endl;
   if (error > 1e-10) { 
       std::cout << "Error - SIGMOID activation test failed" << std::endl;
       return 1;
   }

   error = testSigmoidDerivative<TCuda<Scalar_t>>(10);
   std::cout << "Testing Sigmoid activation derivative:  ";
   std::cout << "maximum relative error = " << error << std::endl;
   if (error > 1e-10) { 
       std::cout << "Error - SIGMOID derivative activation test failed" << std::endl;
       return 1;
   } 
 
   // TanH.

   error = testTanh<TCuda<Scalar_t>>(10);
   std::cout << "Testing TanH activation:                   ";
   std::cout << "maximum relative error = " << print_error(error) << std::endl;
#ifdef R__HAS_VDT   // error is larger when using fast tanh from vdt
    if (error > 1e-6) 
#else
    if (error > 1e-10)
#endif
    { 
       std::cout << "Error - TANH activation test failed" << std::endl;
       return 1;
    }    

   error = testTanhDerivative<TCuda<Scalar_t>>(10);
   std::cout << "Testing TanH activation derivative:        ";
   std::cout << "maximum relative error = " << print_error(error) << std::endl;
#ifdef R__HAS_VDT   // error is larger when using fast tanh from vdt
    if (error > 1e-3) 
#else
    if (error > 1e-10)
#endif
  { 
       std::cout << "Error - TANH derivative activation test failed" << std::endl;
       return 1;
   } 
 
   // Symmetric ReLU.

   error = testSymmetricRelu<TCuda<Scalar_t>>(10);
   std::cout << "Testing Symm. ReLU activation:             ";
   std::cout << "maximum relative error = " << print_error(error) << std::endl;
   if (error > 1e-10)
       return 1;

   error = testSymmetricReluDerivative<TCuda<Scalar_t>>(10);
   std::cout << "Testing Symm. ReLU activation derivative:  ";
   std::cout << "maximum relative error = " << print_error(error) << std::endl;
   if (error > 1e-10)
       return 1;

   // Soft Sign.

   error = testSoftSign<TCuda<Scalar_t>>(10);
   std::cout << "Testing Soft Sign activation:              ";
   std::cout << "maximum relative error = " << print_error(error) << std::endl;
   if (error > 1e-10)
       return 1;

   error = testSoftSignDerivative<TCuda<Scalar_t>>(10);
   std::cout << "Testing Soft Sign activation derivative:   ";
   std::cout << "maximum relative error = " << print_error(error) << std::endl;
   if (error > 1e-10)
       return 1;

   // Gauss.

   error = testGauss<TCuda<Scalar_t>>(10);
   std::cout << "Testing Gauss activation:                  ";
   std::cout << "maximum relative error = " << print_error(error) << std::endl;
   if (error > 1e-10)
       return 1;

   error = testGaussDerivative<TCuda<Scalar_t>>(10);
   std::cout << "Testing Gauss activation derivative:       ";
   std::cout << "maximum relative error = " << print_error(error) << std::endl;
   if (error > 1e-10)
       return 1;

   return 0;
}



//     error = testRelu<TCuda<Scalar_t>>(10);
//     std::cout << "Testing ReLU activation:                ";
//     std::cout << "maximum relative error = " << error << std::endl;
//     if (error > 1e-5)
//         return 1;

//     error = testReluDerivative<TCuda<Scalar_t>>(10);
//     std::cout << "Testing ReLU activation derivative:     ";
//     std::cout << "maximum relative error = " << error << std::endl;
//     if (error > 1e-5)
//         return 1;

//     // Sigmoid.

//     error = testSigmoid<TCuda<Scalar_t>>(10);
//     std::cout << "Testing Sigmoid activation:             ";
//     std::cout << "maximum relative error = " << error << std::endl;
//     if (error > 1e-5)
//         return 1;

//     error = testSigmoidDerivative<TCuda<Scalar_t>>(10);
//     std::cout << "Testing Sigmoid activation derivative:  ";
//     std::cout << "maximum relative error = " << error << std::endl;
//     if (error > 1e-5)
//         return 1;
//     return 0;
// }
