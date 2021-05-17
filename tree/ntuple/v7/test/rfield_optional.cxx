#include "ntuple_test.hxx"

#if __cplusplus >= 201703L
TEST(RNTuple, Optional)
{
   FileRaii fileGuard("test_ntuple_optional.root");

   auto model = RNTupleModel::Create();
   auto field = model->MakeField<std::optional<double>>({"opt", "some optional field"}, 3.0);
   {
      auto ntuple = RNTupleWriter::Recreate(std::move(model), "myNTuple", fileGuard.GetPath());
      *field = std::nullopt;
      ntuple->Fill();
      *field = 42.0;
      ntuple->Fill();
      *field = 100.0;
      ntuple->Fill();
   }

   auto ntuple = RNTupleReader::Open("myNTuple", fileGuard.GetPath());
   ntuple->PrintInfo();
   auto viewOpt = ntuple->GetView<std::optional<double>>("opt");
   EXPECT_FALSE(viewOpt(0).has_value());
   EXPECT_EQ(42.0, viewOpt(1).value());
   EXPECT_EQ(100.0, viewOpt(2).value());
}

#else
TEST(RNTuple, OptionalNotSupported)
{
}
#endif // __cplusplus >= 201703L
