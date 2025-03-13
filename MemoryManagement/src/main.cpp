/**
 * @file main.cpp
 * @author Abdelrahman Emad (a.emad02018@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-12-24
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <string>
#include <vector>
#include <iostream>
#include "copySemantics.hpp"

/**
 * @name main
 * @brief program main function
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, const char *argv[])
{
  /*Test Default Copy*/
  std::cout << "Test Default Copy\n";

  std::cout << "print source data\n";
  DefaultCopy myClass1;
  myClass1.printOwnAddress();
  myClass1.printMemberAddress();

  std::cout << "print destination data\n";
  DefaultCopy myClass2(myClass1); // copy constructor
  myClass2.printOwnAddress();
  myClass2.printMemberAddress();

  /*Test No Copy*/
  std::cout << "Test No Copy\n";
  NoCopy original;
  // NoCopy nocopy1(original);  // copy c’tor
  // NoCopy nocopy2 = original; // assigment operator

  /*Test Exclusive Copy*/
  std::cout << "Test Exclusive Copy\n";

  std::cout << "print source data\n";
  ExclusiveCopy exclusiveCopySource;
  exclusiveCopySource.printOwnAddress();
  exclusiveCopySource.printMemberAddress();

  std::cout << "print destination data\n";
  ExclusiveCopy exclusiveCopydest(exclusiveCopySource);
  exclusiveCopydest.printOwnAddress();
  exclusiveCopydest.printMemberAddress();

  std::cout << "print source data after the copy\n";
  exclusiveCopySource.printOwnAddress();
  exclusiveCopySource.printMemberAddress();

  /*Test Deep Copy*/
  std::cout << "Test Deep Copy\n";

  DeepCopy deepCopySource(42);

  DeepCopy deepCopyDest1(deepCopySource);

  DeepCopy deepCopyDest2 = deepCopyDest1;

  /*Test Shared Copy*/
  std::cout << "Test Shared Copy\n";

  SharedCopy sharedCopySource(42);

  SharedCopy sharedCopyDest1(sharedCopySource);

  SharedCopy sharedCopyDest2 = sharedCopyDest1;

  return 0;
}