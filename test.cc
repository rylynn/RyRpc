  // add manufacture of device for mobile union
  std::string manufacture;
  if (rUserPol.mixer_request() != NULL &&
     !rUserPol.mixer_request()->request_info().manufacturer().empty()) {
    manufacture = rUserPol.mixer_request()->
      request_info().manufacturer();
  }
  else {
    manufacture = jreq["c_mf"].as_stlstring();
    Attr_API(1058967, 1);
  }
o
  if (!manufacture.empty()) {
    device.set_manufacture(manufacture);
    VLOG(500) << "LOG manufacture: " << device.manufacture();
  }  

  // log app market
  for (size_t i = 0; i < rUserPol.app_markets().size(); ++i) {
    device.add_app_market(rUserPol.app_markets()[i]);
    VLOG(500) << "LOG app_market: "
              << rUserPol.app_markets()[i];
  }
  if (rUserPol.is_ios_jail_broken()) {
    device.set_is_ios_jail_broken(true);
  }

  if (!rUserPol.is_muid_type_detected()) {
    VLOG(500) << "LOG muid_type_undetected_reason: "
      << rUserPol.muid_type_undetected_reason();
    if (rUserPol.muid_type_undetected_reason() !=
        device.muid_type_undetected_reason()) {
      device.set_muid_type_undetected_reason(
          rUserPol.muid_type_undetected_reason());
    }
  }
