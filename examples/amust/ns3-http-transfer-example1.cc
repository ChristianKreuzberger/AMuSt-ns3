/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */


#include <iostream>
#include <fstream>
#include <string>


#include "ns3/core-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/node-throughput-tracer.h"
#include "ns3/ipv4-static-routing-helper.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("HttpClientServerTransferExample");


int main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

  // Configure TCP and MTU
  Config::SetDefault("ns3::TcpSocket::SegmentSize", UintegerValue (1430)); // 1460 is too large it seems
  Config::SetDefault("ns3::PointToPointNetDevice::Mtu", UintegerValue (1500)); // ETHERNET MTU
  Config::SetDefault("ns3::TcpL4Protocol::SocketType", StringValue("ns3::TcpNewReno")); // default

  // Configure Network Speed etc...
  Config::SetDefault("ns3::PointToPointNetDevice::DataRate", StringValue("1Mbps"));
  Config::SetDefault("ns3::PointToPointChannel::Delay", StringValue("10ms"));
  Config::SetDefault("ns3::DropTailQueue::MaxPackets", StringValue("20"));

  // Create a 3 node network: client(0) <---> router(1) <---> server(2)
  NodeContainer nodes;
  nodes.Create (3);

  // Name the nodes
  Names::Add("Client", nodes.Get(0));
  Names::Add("Router", nodes.Get(1));
  Names::Add("Server", nodes.Get(2));


  PointToPointHelper p2p; // settings are already defined above
  // Connect client(0) <---> router(1)
  NetDeviceContainer clientToRouterDevices =
    p2p.Install (nodes.Get(0), nodes.Get(1));

  // Connect router(1) <---> server(2)
  NetDeviceContainer serverToRouterDevices =
    p2p.Install (nodes.Get(2), nodes.Get(1));

  // Now add ip/tcp stack to all nodes.
  InternetStackHelper internet;
  internet.InstallAll ();

  // Assign IP Addresses for client(0) <---> router(1)
  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer clientInterfaces = address.Assign (clientToRouterDevices);

  Ipv4Address clientAddress (clientInterfaces.GetAddress (0));


  // Assign IP Addresses for server(2) <---> router(1)
  address.SetBase ("10.1.2.0", "255.255.255.0");
  Ipv4InterfaceContainer serverInterfaces = address.Assign (serverToRouterDevices);

  // Get the servers IP address
  Ipv4Address serverAddress (serverInterfaces.GetAddress (0));

  NS_LOG_UNCOND("ServerAddress=" << serverAddress);
  NS_LOG_UNCOND("ClientAddress=" << clientAddress);


  // Create HTTP Server
  HttpServerHelper server(Ipv4Address::GetAny (), 80, ".", "localhost");
  server.SetAttribute("MetaDataFile", StringValue("fake_fileserver_list.csv"));
  server.SetAttribute("MetaDataDirectory", StringValue("/fake"));

  ApplicationContainer apps = server.Install (nodes.Get(2));

  // Create HTTP Client
  HttpClientHelper client(serverAddress, 80,
    "/fake/fake_large_file_250MB.bin", "testdomain.com");

  client.Install(nodes.Get(0));

  NS_LOG_UNCOND("Installing Routing Tables");
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();


  // Finally, set up the simulator to run.  The 1000 second hard limit is a
  // failsafe in case some change above causes the simulation to never end
  Simulator::Stop (Seconds (3600));
  Simulator::Run ();
  Simulator::Destroy ();

  std::cout << "Done!" << std::endl;
}
