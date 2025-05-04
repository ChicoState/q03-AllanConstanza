/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

TEST(GuesserTest, correctGuess)
{
  Guesser guess("correct");
  ASSERT_TRUE(guess.match("correct"));
  ASSERT_EQ(guess.remaining(), 3);
}

TEST(GuesserTest, GuessesRemainingDontReset) {
	Guesser guess("correctguess");
	ASSERT_FALSE(guess.match("correcthuess"));  
	ASSERT_EQ(guess.remaining(), 2);

	ASSERT_FALSE(guess.match("correctfuess")); 
	ASSERT_EQ(guess.remaining(), 1);

	ASSERT_TRUE(guess.match("correctguess"));   
	ASSERT_FALSE(guess.remaining() == 3);   //guess remaining doesn't reset back to three even after getting correct, should return false 
}



TEST(GuesserTest, LockedAfterDistanceOverTwo){
	Guesser guess("code");
	ASSERT_FALSE(guess.match("dinosaur"));
	ASSERT_FALSE(guess.match("code")); //already locked, wont match or decrement remaining guesses 
	ASSERT_FALSE(guess.remaining() == 2); //should return false, should still be three after locking 
}


TEST(GuesserTest, Over32Length){
	Guesser guess("1234567891234567891234567891234567"); //length over 32
	ASSERT_FALSE(guess.match("1234567891234567891234567891234567")); //should return false, as the length of phrase is over 32
}

TEST(GuesserTest, ThreeWrongGuesses) {
	Guesser guess("correctguess");
	ASSERT_FALSE(guess.match("correcthuess"));
	ASSERT_FALSE(guess.match("correctfuess"));
	ASSERT_FALSE(guess.match("correctiuess"));
	ASSERT_EQ(guess.remaining(), 0); //passes due to 0 remaining guesses after 3 wrong
	ASSERT_FALSE(guess.match("correctguess")); //should return false due to being locked (out of guesses)
}
