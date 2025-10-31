/**
 * @file AquariumTest.cpp
 * @author Cameron Schwindaman
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Aquarium.h>
#include <FishBeta.h>
#include <FishNemo.h>
#include <FishAngel.h>
#include <DecorCastle.h>
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>

using namespace std;

const unsigned int RandomSeed = 1238197374;

class AquariumTest : public ::testing::Test {
protected:
  /**
  * Create a path to a place to put temporary files
  */
  wxString TempPath()
  {
    // Create a temporary filename we can use
    auto path = wxFileName::GetTempDir() + L"/aquarium";
    if(!wxFileName::DirExists(path))
    {
      wxFileName::Mkdir(path);
    }

    return path;
  }

  /**
  * Read a file into a wstring and return it.
  * @param filename Name of the file to read
  * @return File contents
  */
  wstring ReadFile(const wxString &filename)
  {
    ifstream t(filename.ToStdString());
    wstring str((istreambuf_iterator<char>(t)),
            istreambuf_iterator<char>());

    return str;
  }

  /**
   * Test to ensure an aquarium .aqua file is empty
   */
  void TestEmpty(wxString filename)
  {
    cout << "Temp file: " << filename << endl;

    auto xml = ReadFile(filename);
    cout << xml << endl;

    ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
    ASSERT_TRUE(regex_search(xml, wregex(L"<aqua/>")));
  }

  /**
   *  Populate an aquarium with three Beta fish
   */
  void PopulateThreeBetas(Aquarium *aquarium)
  {
    aquarium->GetRandom().seed(RandomSeed);

    auto fish1 = make_shared<FishBeta>(aquarium);
    aquarium->Add(fish1);
    fish1->SetLocation(100, 200);

    auto fish2 = make_shared<FishBeta>(aquarium);
    aquarium->Add(fish2);
    fish2->SetLocation(400, 400);

    auto fish3 = make_shared<FishBeta>(aquarium);
    aquarium->Add(fish3);
    fish3->SetLocation(600, 100);
  }

  void TestThreeBetas(wxString filename)
  {
    cout << "Temp file: " << filename << endl;

    auto xml = ReadFile(filename);
    cout << xml << endl;

    // Ensure three items
    ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*</aqua>")));

    // Ensure the positions and speeds are correct
    ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\" speedx=\"34\\.6892.*\" speedy=\"40\\.6032.*\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\" speedx=\"40\\.6797.*\" speedy=\"42\\.1756.*\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\" speedx=\"48\\.756.*\" speedy=\"49\\.6308.*\"")));

    // Ensure the types are correct
    ASSERT_TRUE(regex_search(xml,
            wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"beta\"/><item.* type=\"beta\"/></aqua>")));
  }

  /**
   *  Populate an aquarium with all type of items
   */
  void PopulateAllTypes(Aquarium *aquarium)
  {
    aquarium->GetRandom().seed(RandomSeed);

    auto fish1 = make_shared<FishBeta>(aquarium);
    aquarium->Add(fish1);
    fish1->SetLocation(100, 200);

    auto fish2 = make_shared<FishNemo>(aquarium);
    aquarium->Add(fish2);
    fish2->SetLocation(400, 400);

    auto fish3 = make_shared<FishAngel>(aquarium);
    aquarium->Add(fish3);
    fish3->SetLocation(600, 100);

    auto fish4 = make_shared<DecorCastle>(aquarium);
    aquarium->Add(fish4);
    fish4->SetLocation(300, 300);
  }

  void TestAllTypes(wxString filename)
  {
    cout << "Temp file: " << filename << endl;

    auto xml = ReadFile(filename);
    cout << xml << endl;

    // Ensure four items
    ASSERT_TRUE(regex_search(xml, wregex(L"<aqua><item.*<item.*<item.*<item.*</aqua>")));

    // Ensure the positions and speeds are correct
    ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"100\" y=\"200\" speedx=\"34\\.6892.*\" speedy=\"40\\.6032.*\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"400\" y=\"400\" speedx=\"68\\.756.*\" speedy=\"69\\.6308.*\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"600\" y=\"100\" speedx=\"11\\.2288.*\" speedy=\"17\\.0998.*\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"<item x=\"300\" y=\"300\"")));

    // Ensure the types are correct
    ASSERT_TRUE(regex_search(xml,
            wregex(L"<aqua><item.* type=\"beta\"/><item.* type=\"nemo\"/><item.* type=\"angel\"/><item.* type=\"castle\"/></aqua>")));
  }
};

TEST_F(AquariumTest, Construct){
    Aquarium aquarium;
}

TEST_F(AquariumTest, HitTest) {
    Aquarium aquarium;

    ASSERT_EQ(aquarium.HitTest(100, 200), nullptr) <<
        L"Testing empty aquarium";

    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish1);
    fish1->SetLocation(100, 200);

    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish1) <<
          L"Testing fish at 100, 200";

    ASSERT_TRUE(aquarium.HitTest(10, 200) == nullptr) <<
      L"Testing fish at 10, 200";

    ASSERT_TRUE(aquarium.HitTest(200, 200) == nullptr) <<
      L"Testing fish at 200, 200";

    ASSERT_TRUE(aquarium.HitTest(100, 0) == nullptr) <<
      L"Testing fish at 100, 0";

    ASSERT_TRUE(aquarium.HitTest(100, 300) == nullptr) <<
      L"Testing fish at 100, 300";

    ASSERT_TRUE(aquarium.HitTest(100 - 125/2 + 17, 200 - 117/2 + 16) == nullptr) <<
      L"Testing fish at transparent pixel";

    shared_ptr<FishBeta> fish2 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish2);
    fish2->SetLocation(100, 200);

    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish2) <<
      L"Testing fish at 100, 200";
}

TEST_F(AquariumTest, Save) {
  // Create a path to temporary files
  auto path = TempPath();

  // Create an aquarium
  Aquarium aquarium;

  //
  // First test, saving an empty aquarium
  //
  auto file1 = path + L"/test1.aqua";
  aquarium.Save(file1);

  TestEmpty(file1);

  //
  // Now populate the aquarium
  //

  PopulateThreeBetas(&aquarium);

  auto file2 = path + L"/test2.aqua";
  aquarium.Save(file2);

  TestThreeBetas(file2);

  //
  // Test all types
  //
  Aquarium aquarium3;
  PopulateAllTypes(&aquarium3);

  auto file3 = path + L"/test3.aqua";
  aquarium3.Save(file3);

  TestAllTypes(file3);
}

TEST_F(AquariumTest, Clear) {
  auto path = TempPath();

  Aquarium aquarium;

  PopulateThreeBetas(&aquarium);

  auto file = path + L"/test1.aqua";
  aquarium.Save(file);
  TestThreeBetas(file);

  aquarium.Clear();

  auto file2 = path + L"/test2.aqua";
  aquarium.Save(file2);
  TestEmpty(file2);
}

TEST_F(AquariumTest, Load) {
  // Create a path to temporary files
  auto path = TempPath();

  // Create an aquarium
  Aquarium aquarium;
  Aquarium aquarium2;

  //
  // First test, saving an empty aquarium
  //
  auto file1 = path + L"/test1.aqua";
  aquarium.Save(file1);

  TestEmpty(file1);

  aquarium2.Load(file1);
  aquarium2.Save(file1);
  TestEmpty(file1);

  //
  // Now populate the aquarium
  //

  PopulateThreeBetas(&aquarium);

  wstring file2 = path + L"/test2.aqua";
  aquarium.Save(file2);
  TestThreeBetas(file2);

  //
  // Test all types
  //
  Aquarium aquarium3;
  PopulateAllTypes(&aquarium3);

  wstring file3 = path + L"/test3.aqua";
  aquarium3.Save(file3);
  TestAllTypes(file3);

  aquarium2.Load(file2);
  aquarium2.Save(file2);
  TestThreeBetas(file2);

  aquarium3.Load(file3);
  aquarium3.Save(file3);
  TestAllTypes(file3);
}