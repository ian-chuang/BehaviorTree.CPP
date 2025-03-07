#include "behaviortree_cpp/loggers/bt_cout_logger.h"

namespace BT
{
std::atomic<bool> StdCoutLogger::ref_count(false);

StdCoutLogger::StdCoutLogger(const BT::Tree& tree) : StatusChangeLogger(tree.rootNode())
{
  bool expected = false;
  if (!ref_count.compare_exchange_strong(expected, true))
  {
    throw LogicError("Only one instance of StdCoutLogger shall be created");
  }
}
StdCoutLogger::~StdCoutLogger()
{
  ref_count.store(false);
}

void StdCoutLogger::callback(Duration timestamp, const TreeNode& node,
                             NodeStatus prev_status, NodeStatus status)
{
  using namespace std::chrono;

  constexpr const char* whitespaces = "                         ";
  constexpr const size_t ws_count = 25;

    double since_epoch = duration<double>(timestamp).count();
    printf("[%.3f]: %s%s %s -> %s",
           since_epoch, node.short_description().c_str(),
           &whitespaces[std::min(ws_count, node.short_description().size())],
           toStr(prev_status, true).c_str(),
           toStr(status, true).c_str() );
    std::cout << std::endl;
}

void StdCoutLogger::flush()
{
  std::cout << std::flush;
  ref_count = false;
}

}   // namespace BT
