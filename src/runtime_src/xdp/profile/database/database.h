/**
 * Copyright (C) 2016-2020 Xilinx, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You may
 * not use this file except in compliance with the License. A copy of the
 * License is located at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#ifndef VTF_DATABASE_DOT_H
#define VTF_DATABASE_DOT_H

#include <vector>
#include <list>

#include "xdp/profile/database/statistics_database.h"
#include "xdp/profile/database/static_info_database.h"
#include "xdp/profile/database/dynamic_event_database.h"

namespace xdp {

  // Forward declarations
  class XDPPlugin ;

  // There will be one database per application, regardless of how
  //  many plugins are created.  All plugins will have a reference to
  //  this single database.  Therefore this class utilizes the
  //  singleton pattern.
  class VPDatabase
  {
  private:
    // The information stored in the database will be separated into 
    //  three sections:
    //    1 - Counter information used for statistics
    //    2 - Static information based on the xclbin that is loaded
    //    3 - Dynamic events from both host and hardware
    VPStatisticsDatabase stats ;
    VPStaticDatabase staticdb ;
    VPDynamicDatabase dyndb ;

    // A list of all registered plugins.  These will be used when
    //  portions of the database are reset and when the database is
    //  destroyed at the end of execution.
    std::list<XDPPlugin*> plugins ;

  private:
    VPDatabase() ;

    static bool live ;

  public:
    ~VPDatabase() ;
    static VPDatabase* Instance() ;
    static bool alive() ;

    // Access to the three different types of information
    inline VPStatisticsDatabase& getStats()       { return stats ; }
    inline VPStaticDatabase&     getStaticInfo()  { return staticdb ; }
    inline VPDynamicDatabase&    getDynamicInfo() { return dyndb ; }

    // Functions that plugins call on startup and destruction
    inline void registerPlugin(XDPPlugin* p)   { plugins.push_back(p) ; }
    inline void unregisterPlugin(XDPPlugin* p) { plugins.remove(p) ; }
  } ;
}

#endif
