/*
   This file is part of Kismet

   Kismet is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   Kismet is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Kismet; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
   */

#ifndef __PHY_80211_COMPONENTS_H__
#define __PHY_80211_COMPONENTS_H__

#include "config.h"

#include <time.h>

#include <algorithm>
#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>

#ifdef HAVE_LIBPCRE
#include <pcre.h>
#endif

#include "devicetracker_component.h"
#include "entrytracker.h"
#include "globalregistry.h"
#include "trackedcomponent.h"

#include "dot11_parsers/dot11_ie.h"
#include "dot11_parsers/dot11_ie_221_vendor.h"
#include "dot11_parsers/dot11_ie_255_ext_tag.h"

class dot11_tracked_eapol : public tracker_component {
public:
    dot11_tracked_eapol() :
        tracker_component() {
        register_fields();
        reserve_fields(NULL);
    }

    dot11_tracked_eapol(int in_id) :
        tracker_component(in_id) {
            register_fields();
            reserve_fields(NULL);
        }

    dot11_tracked_eapol(int in_id, std::shared_ptr<tracker_element_map> e) : 
        tracker_component(in_id) {
        register_fields();
        reserve_fields(e);
    }

    dot11_tracked_eapol(const dot11_tracked_eapol *p) :
        tracker_component{p} {

        eapol_time = tracker_element_clone_adaptor(p->eapol_time);
        eapol_dir = tracker_element_clone_adaptor(p->eapol_dir);
        eapol_replay_counter = tracker_element_clone_adaptor(p->eapol_replay_counter);
        eapol_msg_num = tracker_element_clone_adaptor(p->eapol_msg_num);
        eapol_install = tracker_element_clone_adaptor(p->eapol_install);
        eapol_nonce = tracker_element_clone_adaptor(p->eapol_nonce);
        eapol_rsn_pmkid = tracker_element_clone_adaptor(p->eapol_rsn_pmkid);

        eapol_packet = tracker_element_clone_adaptor(p->eapol_packet);
        eapol_packet_id = p->eapol_packet_id;

        reserve_fields(nullptr);
    }

    virtual uint32_t get_signature() const override {
        return adler32_checksum("dot11_tracked_eapol");
    }

    virtual std::unique_ptr<tracker_element> clone_type() override {
        using this_t = std::remove_pointer<decltype(this)>::type;
        auto dup = std::unique_ptr<this_t>(new this_t(this));
        return std::move(dup);
    }

    __Proxy(eapol_time, double, double, double, eapol_time);
    __Proxy(eapol_dir, uint8_t, uint8_t, uint8_t, eapol_dir);
    __Proxy(eapol_replay_counter, uint64_t, uint64_t, uint64_t, eapol_replay_counter);
    __Proxy(eapol_msg_num, uint8_t, uint8_t, uint8_t, eapol_msg_num);
    __Proxy(eapol_install, uint8_t, bool, bool, eapol_install);

    __ProxyTrackable(eapol_nonce, tracker_element_byte_array, eapol_nonce);
    void set_eapol_nonce_bytes(const std::string& in_n) { eapol_nonce->set(in_n); }
    std::string get_eapol_nonce_bytes() { return eapol_nonce->get(); }

    __ProxyTrackable(eapol_rsn_pmkid, tracker_element_byte_array, eapol_rsn_pmkid);
    void set_rsnpmkid_bytes(const std::string& in_n) { eapol_rsn_pmkid->set(in_n); }
    std::string get_rsnpmkid_bytes() { return eapol_rsn_pmkid->get(); }

    __ProxyTrackable(eapol_packet, kis_tracked_packet, eapol_packet);

protected:
    virtual void register_fields() override;

    std::shared_ptr<tracker_element_double> eapol_time;
    std::shared_ptr<tracker_element_uint8> eapol_dir;
    std::shared_ptr<tracker_element_uint64> eapol_replay_counter;
    std::shared_ptr<tracker_element_uint8> eapol_msg_num;
    std::shared_ptr<tracker_element_uint8> eapol_install;
    std::shared_ptr<tracker_element_byte_array> eapol_nonce;
    std::shared_ptr<tracker_element_byte_array> eapol_rsn_pmkid;

    std::shared_ptr<kis_tracked_packet> eapol_packet;
    int eapol_packet_id;
};

class dot11_tracked_nonce : public tracker_component {
public:
    dot11_tracked_nonce() :
        tracker_component() {
        register_fields();
        reserve_fields(NULL);
    }

    dot11_tracked_nonce(int in_id) :
        tracker_component(in_id) {
        register_fields();
        reserve_fields(NULL);
    }

    dot11_tracked_nonce(int in_id, std::shared_ptr<tracker_element_map> e) : 
        tracker_component(in_id) {
        register_fields();
        reserve_fields(e);
    }

    dot11_tracked_nonce(const dot11_tracked_nonce *p) :
        tracker_component{p} {
        eapol_time = tracker_element_clone_adaptor(p->eapol_time);
        eapol_msg_num = tracker_element_clone_adaptor(p->eapol_msg_num);
        eapol_install = tracker_element_clone_adaptor(p->eapol_install);
        eapol_nonce = tracker_element_clone_adaptor(p->eapol_nonce);
        eapol_replay_counter = tracker_element_clone_adaptor(p->eapol_replay_counter);
        reserve_fields(nullptr);
    }

    virtual uint32_t get_signature() const override {
        return adler32_checksum("dot11_tracked_nonce");
    }

    virtual std::unique_ptr<tracker_element> clone_type() override {
        using this_t = std::remove_pointer<decltype(this)>::type;
        auto dup = std::unique_ptr<this_t>(new this_t(this));
        return std::move(dup);
    }

    __Proxy(eapol_time, double, double, double, eapol_time);
    __Proxy(eapol_msg_num, uint8_t, uint8_t, uint8_t, eapol_msg_num);
    __Proxy(eapol_install, uint8_t, bool, bool, eapol_install);
    __Proxy(eapol_replay_counter, uint64_t, uint64_t, uint64_t, eapol_replay_counter);

    void set_eapol_nonce_bytes(std::string in_n) {
        eapol_nonce->set(in_n);
    }

    std::string get_eapol_nonce_bytes() {
        return eapol_nonce->get();
    }

    void set_from_eapol(shared_tracker_element in_tracked_eapol);

protected:
    virtual void register_fields() override;

    std::shared_ptr<tracker_element_double> eapol_time;
    std::shared_ptr<tracker_element_uint8> eapol_msg_num;
    std::shared_ptr<tracker_element_uint8> eapol_install;
    std::shared_ptr<tracker_element_byte_array> eapol_nonce;
    std::shared_ptr<tracker_element_uint64> eapol_replay_counter;
};

class dot11_tracked_ssid_alert : public tracker_component {
public:
    dot11_tracked_ssid_alert() :
        tracker_component() {
#ifdef HAVE_LIBPCRE
        ssid_re = NULL;
        ssid_study = NULL;
#endif

        register_fields();
        reserve_fields(NULL);
    };

    dot11_tracked_ssid_alert(int in_id) :
        tracker_component(in_id) {

#ifdef HAVE_LIBPCRE
            ssid_re = NULL;
            ssid_study = NULL;
#endif

            register_fields();
            reserve_fields(NULL);
        }

    dot11_tracked_ssid_alert(int in_id, std::shared_ptr<tracker_element_map> e) :
        tracker_component(in_id) {
#ifdef HAVE_LIBCPRE
        ssid_re = NULL;
        ssid_study = NULL;
#endif

        register_fields();
        reserve_fields(e);
    }

    dot11_tracked_ssid_alert(const dot11_tracked_ssid_alert *p) :
        tracker_component{p} {
#ifdef HAVE_LIBCPRE
        ssid_re = NULL;
        ssid_study = NULL;
#endif
        ssid_group_name = tracker_element_clone_adaptor(p->ssid_group_name);
        ssid_regex = tracker_element_clone_adaptor(p->ssid_regex);
        allowed_macs_vec = tracker_element_clone_adaptor(p->allowed_macs_vec);
        allowed_mac_id = p->allowed_mac_id;

        reserve_fields(nullptr);
    }

    virtual ~dot11_tracked_ssid_alert() {
#ifdef HAVE_LIBCPRE
        if (ssid_re != NULL)
            pcre_free(ssid_re);
        if (ssid_study != NULL)
            pcre_free(ssid_study);
#endif
    }

    virtual uint32_t get_signature() const override {
        return adler32_checksum("dot11_tracked_ssid_alert");
    }

    virtual std::unique_ptr<tracker_element> clone_type() override {
        using this_t = std::remove_pointer<decltype(this)>::type;
        auto dup = std::unique_ptr<this_t>(new this_t(this));
        return std::move(dup);
    }

    __Proxy(group_name, std::string, std::string, std::string, ssid_group_name);

    // Control the regex.  MAY THROW std::runtime_error if the regex is invalid
    __ProxyGet(regex, std::string, std::string, ssid_regex);
    void set_regex(std::string s);

    __ProxyTrackable(allowed_macs_vec, tracker_element_vector, allowed_macs_vec);

    void set_allowed_macs(std::vector<mac_addr> mvec);

    bool compare_ssid(std::string ssid, mac_addr mac);

protected:
    kis_recursive_timed_mutex ssid_mutex;

    virtual void register_fields() override;

    std::shared_ptr<tracker_element_string> ssid_group_name;
    std::shared_ptr<tracker_element_string> ssid_regex;
    std::shared_ptr<tracker_element_vector> allowed_macs_vec;
    int allowed_mac_id;

#ifdef HAVE_LIBPCRE
    pcre *ssid_re;
    pcre_extra *ssid_study;
#endif
};

class dot11_11d_tracked_range_info : public tracker_component {
public:
    dot11_11d_tracked_range_info() :
        tracker_component() {
        register_fields();
        reserve_fields(NULL);
    }

    dot11_11d_tracked_range_info(int in_id) :
        tracker_component(in_id) {
        register_fields();
        reserve_fields(NULL);
    }

    dot11_11d_tracked_range_info(int in_id, std::shared_ptr<tracker_element_map> e) : 
        tracker_component(in_id) {
        register_fields();
        reserve_fields(e);
    }

    dot11_11d_tracked_range_info(const dot11_11d_tracked_range_info *p) :
        tracker_component{p} {

        startchan = tracker_element_clone_adaptor(p->startchan);
        numchan = tracker_element_clone_adaptor(p->numchan);
        txpower = tracker_element_clone_adaptor(p->txpower);

        reserve_fields(nullptr);
    }

    virtual uint32_t get_signature() const override {
        return adler32_checksum("dot11_11d_tracked_range_info");
    }

    virtual std::unique_ptr<tracker_element> clone_type() override {
        using this_t = std::remove_pointer<decltype(this)>::type;
        auto dup = std::unique_ptr<this_t>(new this_t(this));
        return std::move(dup);
    }

    __Proxy(startchan, uint32_t, uint32_t, uint32_t, startchan);
    __Proxy(numchan, uint32_t, unsigned int, unsigned int, numchan);
    __Proxy(txpower, int32_t, int, int, txpower);

protected:
    virtual void register_fields() override {
        register_field("dot11.11d.start_channel", "Starting channel of 11d range", &startchan);
        register_field("dot11.11d.num_channels", "Number of channels covered by range", &numchan);
        register_field("dot11.11d.tx_power", "Maximum allowed transmit power", &txpower);
    }

    std::shared_ptr<tracker_element_uint32> startchan;
    std::shared_ptr<tracker_element_uint32> numchan;
    std::shared_ptr<tracker_element_int32> txpower;
};

class dot11_tracked_ietag : public tracker_component {
public:
    dot11_tracked_ietag() :
        tracker_component() {
        register_fields();
        reserve_fields(NULL);
    }

    dot11_tracked_ietag(int in_id) :
        tracker_component(in_id) {
        register_fields();
        reserve_fields(NULL);
    }

    dot11_tracked_ietag(int in_id, std::shared_ptr<tracker_element_map> e) : 
        tracker_component(in_id) {
        register_fields();
        reserve_fields(e);
    }

    dot11_tracked_ietag(const dot11_tracked_ietag *p) {
        unique_tag_id = tracker_element_clone_adaptor(p->unique_tag_id);
        tag_number = tracker_element_clone_adaptor(p->tag_number);
        tag_oui = tracker_element_clone_adaptor(p->tag_oui);
        tag_vendor_or_sub = tracker_element_clone_adaptor(p->tag_vendor_or_sub);
        complete_tag_data = tracker_element_clone_adaptor(p->complete_tag_data);

        reserve_fields(nullptr);
    }


    virtual uint32_t get_signature() const override {
        return adler32_checksum("dot11_tracked_ietag");
    }

    virtual std::unique_ptr<tracker_element> clone_type() override {
        using this_t = std::remove_pointer<decltype(this)>::type;
        auto dup = std::unique_ptr<this_t>(new this_t(this));
        return std::move(dup);
    }

    __Proxy(unique_tag_id, uint32_t, uint32_t, uint32_t, unique_tag_id);
    __Proxy(tag_number, uint8_t, uint8_t, uint8_t, tag_number);
    __Proxy(tag_oui, uint32_t, uint32_t, uint32_t, tag_oui);
    __Proxy(tag_oui_manuf, std::string, std::string, std::string, tag_oui_manuf);
    __Proxy(tag_vendor_or_sub, int16_t, int16_t, int16_t, tag_vendor_or_sub);
    __Proxy(complete_tag_data, std::string, std::string, std::string, complete_tag_data);

    void set_from_tag(std::shared_ptr<dot11_ie::dot11_ie_tag> ie);

protected:
    virtual void register_fields() override;

    std::shared_ptr<tracker_element_uint32> unique_tag_id;
    std::shared_ptr<tracker_element_uint8> tag_number;
    std::shared_ptr<tracker_element_uint32> tag_oui;
    std::shared_ptr<tracker_element_string> tag_oui_manuf;
    std::shared_ptr<tracker_element_int16> tag_vendor_or_sub;
    std::shared_ptr<tracker_element_byte_array> complete_tag_data;
};

class dot11_probed_ssid : public tracker_component {
public:
    dot11_probed_ssid() :
        tracker_component() {
        register_fields();
        reserve_fields(NULL);
    }

    dot11_probed_ssid(int in_id) : 
        tracker_component(in_id) { 
            register_fields();
            reserve_fields(NULL);
        } 

    dot11_probed_ssid(int in_id, std::shared_ptr<tracker_element_map> e) : 
        tracker_component(in_id) {
            register_fields();
            reserve_fields(e);
        }

    dot11_probed_ssid(const dot11_probed_ssid *p) :
        tracker_component{p} {
            ssid = tracker_element_clone_adaptor(p->ssid);
            ssid_len = tracker_element_clone_adaptor(p->ssid_len);
            bssid = tracker_element_clone_adaptor(p->bssid);
            first_time = tracker_element_clone_adaptor(p->first_time);
            last_time = tracker_element_clone_adaptor(p->last_time);
            dot11r_mobility = tracker_element_clone_adaptor(p->dot11r_mobility);
            dot11r_mobility_domain_id = tracker_element_clone_adaptor(p->dot11r_mobility_domain_id);

            location_id = p->location_id;

            crypt_set = tracker_element_clone_adaptor(p->crypt_set);
            wpa_mfp_required = tracker_element_clone_adaptor(p->wpa_mfp_required);
            wpa_mfp_supported = tracker_element_clone_adaptor(p->wpa_mfp_supported);

            ie_tag_list_id = p->ie_tag_list_id;

            wps_state_id = p->wps_state_id;

            wps_manuf_id = p->wps_manuf_id;

            wps_device_name_id = p->wps_device_name_id;

            wps_model_name_id = p->wps_model_name_id;

            wps_model_number_id = p->wps_model_number_id;

            wps_serial_number_id = p->wps_serial_number_id;

            wps_uuid_e_id = p->wps_uuid_e_id;

            reserve_fields(nullptr);
        }

    virtual uint32_t get_signature() const override {
        return adler32_checksum("dot11_probed_ssid");
    }

    virtual std::unique_ptr<tracker_element> clone_type() override {
        using this_t = std::remove_pointer<decltype(this)>::type;
        auto dup = std::unique_ptr<this_t>(new this_t(this));
        return std::move(dup);
    }

    __Proxy(ssid, std::string, std::string, std::string, ssid);
    __Proxy(ssid_len, uint32_t, unsigned int, unsigned int, ssid_len);
    __Proxy(bssid, mac_addr, mac_addr, mac_addr, bssid);
    __Proxy(first_time, uint64_t, time_t, time_t, first_time);
    __Proxy(last_time, uint64_t, time_t, time_t, last_time);

    __ProxyDynamicTrackable(location, kis_tracked_location, location, location_id);

    __Proxy(dot11r_mobility, uint8_t, bool, bool, dot11r_mobility);
    __Proxy(dot11r_mobility_domain_id, uint16_t, uint16_t, uint16_t, dot11r_mobility_domain_id);

    __Proxy(crypt_set, uint64_t, uint64_t, uint64_t, crypt_set);
    __Proxy(wpa_mfp_required, uint8_t, bool, bool, wpa_mfp_required);
    __Proxy(wpa_mfp_supported, uint8_t, bool, bool, wpa_mfp_supported);

    __ProxyDynamicTrackable(ie_tag_list, tracker_element_vector_double, ie_tag_list, ie_tag_list_id);

    __ProxyDynamic(wps_state, uint32_t, uint32_t, uint32_t, wps_state, wps_state_id);
    __ProxyDynamic(wps_manuf, std::string, std::string, std::string, wps_manuf, wps_manuf_id);
    __ProxyDynamic(wps_device_name, std::string, std::string, std::string, wps_device_name, wps_device_name_id);
    __ProxyDynamic(wps_model_name, std::string, std::string, std::string, wps_model_name, wps_model_name_id);
    __ProxyDynamic(wps_model_number, std::string, std::string, std::string, wps_model_number, wps_model_number_id);
    __ProxyDynamic(wps_serial_number, std::string, std::string, std::string, wps_serial_number, wps_serial_number_id);
    __ProxyDynamic(wps_uuid_e, std::string, std::string, std::string, wps_uuid_e, wps_uuid_e_id);

protected:
    virtual void register_fields() override;

    std::shared_ptr<tracker_element_string> ssid;
    std::shared_ptr<tracker_element_uint32> ssid_len;
    std::shared_ptr<tracker_element_mac_addr> bssid;
    std::shared_ptr<tracker_element_uint64> first_time;
    std::shared_ptr<tracker_element_uint64> last_time;

    std::shared_ptr<tracker_element_uint8> dot11r_mobility;
    std::shared_ptr<tracker_element_uint16> dot11r_mobility_domain_id;

    std::shared_ptr<kis_tracked_location> location;
    int location_id;

    std::shared_ptr<tracker_element_uint64> crypt_set;
    std::shared_ptr<tracker_element_uint8> wpa_mfp_required;
    std::shared_ptr<tracker_element_uint8> wpa_mfp_supported;

    std::shared_ptr<tracker_element_vector_double> ie_tag_list;
    int ie_tag_list_id;

    // WPS components
    std::shared_ptr<tracker_element_uint32> wps_state;
    int wps_state_id;

    std::shared_ptr<tracker_element_string> wps_manuf;
    int wps_manuf_id;

    std::shared_ptr<tracker_element_string> wps_device_name;
    int wps_device_name_id;

    std::shared_ptr<tracker_element_string> wps_model_name;
    int wps_model_name_id;

    std::shared_ptr<tracker_element_string> wps_model_number;
    int wps_model_number_id;

    std::shared_ptr<tracker_element_string> wps_serial_number;
    int wps_serial_number_id;

    std::shared_ptr<tracker_element_byte_array> wps_uuid_e;
    int wps_uuid_e_id;
};

/* Advertised SSID
 *
 * SSID advertised by a device via beacon or probe response
 */
class dot11_packinfo_dot11d_entry;

class dot11_advertised_ssid : public tracker_component {
public:
    dot11_advertised_ssid() :
        tracker_component() {
        register_fields();
        reserve_fields(NULL);
    }

    dot11_advertised_ssid(int in_id) : 
        tracker_component(in_id) { 
            register_fields();
            reserve_fields(NULL);
        } 

    dot11_advertised_ssid(int in_id, std::shared_ptr<tracker_element_map> e) : 
        tracker_component(in_id) {
            register_fields();
            reserve_fields(e);
        }

    dot11_advertised_ssid(const dot11_advertised_ssid *p) :
        tracker_component{p} {
            ssid = tracker_element_clone_adaptor(p->ssid);
            ssid_len = tracker_element_clone_adaptor(p->ssid_len);
            ssid_hash = tracker_element_clone_adaptor(p->ssid_hash);

            owe_ssid_id = p->owe_ssid_id;

            owe_ssid_len_id = p->owe_ssid_len_id;

            owe_bssid_id = p->owe_bssid_id;

            ssid_beacon = tracker_element_clone_adaptor(p->ssid_beacon);
            ssid_probe_response = tracker_element_clone_adaptor(p->ssid_probe_response);

            channel = tracker_element_clone_adaptor(p->channel);
            ht_mode = tracker_element_clone_adaptor(p->ht_mode);
            ht_center_1 = tracker_element_clone_adaptor(p->ht_center_1);
            ht_center_2 = tracker_element_clone_adaptor(p->ht_center_2);

            first_time = tracker_element_clone_adaptor(p->first_time);
            last_time = tracker_element_clone_adaptor(p->last_time);

            beacon_info_id = p->beacon_info_id;

            ssid_cloaked = tracker_element_clone_adaptor(p->ssid_cloaked);
            crypt_set = tracker_element_clone_adaptor(p->crypt_set);
            wpa_mfp_required = tracker_element_clone_adaptor(p->wpa_mfp_required);
            wpa_mfp_supported = tracker_element_clone_adaptor(p->wpa_mfp_supported);
            beaconrate = tracker_element_clone_adaptor(p->beaconrate);
            beacons_sec = tracker_element_clone_adaptor(p->beacons_sec);
            ietag_checksum = tracker_element_clone_adaptor(p->ietag_checksum);

            dot11d_country_id = p->dot11d_country_id;

            dot11d_vec_id = p->dot11d_vec_id;
            dot11d_country_entry_id = p->dot11d_country_entry_id;

            wps_state_id = p->wps_state_id;
            wps_manuf_id = p->wps_manuf_id;
            wps_device_name_id = p->wps_device_name_id;
            wps_model_name_id = p->wps_model_name_id;
            wps_model_number_id = p->wps_model_number_id;
            wps_serial_number_id = p->wps_serial_number_id;
            wps_uuid_e_id = p->wps_uuid_e_id;

            location_id = p->location_id;

            dot11r_mobility = tracker_element_clone_adaptor(p->dot11r_mobility);
            dot11r_mobility_domain_id = tracker_element_clone_adaptor(p->dot11r_mobility_domain_id);

            dot11e_qbss = tracker_element_clone_adaptor(p->dot11e_qbss);
            dot11e_qbss_stations = tracker_element_clone_adaptor(p->dot11e_qbss_stations);
            dot11e_qbss_channel_load = tracker_element_clone_adaptor(p->dot11e_qbss_channel_load);

            ccx_txpower = tracker_element_clone_adaptor(p->ccx_txpower);
            cisco_client_mfp = tracker_element_clone_adaptor(p->cisco_client_mfp);

            ie_tag_list_id = p->ie_tag_list_id;
            ie_tag_content_id = p->ie_tag_content_id;
            ie_tag_content_element_id = p->ie_tag_content_element_id;

            reserve_fields(nullptr);
        }

    virtual uint32_t get_signature() const override {
        return adler32_checksum("dot11_advertised_ssid");
    }

    virtual std::unique_ptr<tracker_element> clone_type() override {
        using this_t = std::remove_pointer<decltype(this)>::type;
        auto dup = std::unique_ptr<this_t>(new this_t(this));
        return std::move(dup);
    }

    __Proxy(ssid, std::string, std::string, std::string, ssid);
    __Proxy(ssid_len, uint32_t, unsigned int, unsigned int, ssid_len);

    __Proxy(ssid_hash, uint64_t, uint64_t, uint64_t, ssid_hash);

    __ProxyDynamic(owe_ssid, std::string, std::string, std::string, owe_ssid, owe_ssid_id);
    __ProxyDynamic(owe_ssid_len, uint32_t, unsigned, unsigned int, owe_ssid_len, owe_ssid_len_id);
    __ProxyDynamic(owe_bssid, mac_addr, mac_addr, mac_addr, owe_bssid, owe_bssid_id);

    __Proxy(ssid_beacon, uint8_t, bool, bool, ssid_beacon);
    __Proxy(ssid_probe_response, uint8_t, bool, bool, ssid_probe_response);

    __Proxy(channel, std::string, std::string, std::string, channel);
    __Proxy(ht_mode, std::string, std::string, std::string, ht_mode);
    __Proxy(ht_center_1, uint64_t, uint64_t, uint64_t, ht_center_1);
    __Proxy(ht_center_2, uint64_t, uint64_t, uint64_t, ht_center_2);

    __Proxy(first_time, uint64_t, time_t, time_t, first_time);
    __Proxy(last_time, uint64_t, time_t, time_t, last_time);

    __ProxyDynamic(beacon_info, std::string, std::string, std::string, beacon_info, beacon_info_id);

    __Proxy(ssid_cloaked, uint8_t, bool, bool, ssid_cloaked);

    __Proxy(crypt_set, uint64_t, uint64_t, uint64_t, crypt_set);

    // WPA MFP
    __Proxy(wpa_mfp_required, uint8_t, bool, bool, wpa_mfp_required);
    __Proxy(wpa_mfp_supported, uint8_t, bool, bool, wpa_mfp_supported);

    __Proxy(maxrate, double, double, double, maxrate);

    __Proxy(beaconrate, uint32_t, uint32_t, uint32_t, beaconrate);
    __Proxy(beacons_sec, uint32_t, uint32_t, uint32_t, beacons_sec);
    __ProxyIncDec(beacons_sec, uint32_t, uint32_t, beacons_sec);

    __Proxy(ietag_checksum, uint32_t, uint32_t, uint32_t, ietag_checksum);

    __ProxyDynamic(dot11d_country, std::string, std::string, std::string, dot11d_country, 
            dot11d_country_id);

    __ProxyDynamicTrackable(dot11d_vec, tracker_element_vector, dot11d_vec, dot11d_vec_id);
    void set_dot11d_vec(std::vector<dot11_packinfo_dot11d_entry> vec);

    __ProxyDynamic(wps_state, uint32_t, uint32_t, uint32_t, wps_state, wps_state_id);
    __ProxyDynamic(wps_manuf, std::string, std::string, std::string, wps_manuf, wps_manuf_id);
    __ProxyDynamic(wps_device_name, std::string, std::string, std::string, wps_device_name, 
            wps_device_name_id);
    __ProxyDynamic(wps_model_name, std::string, std::string, std::string, wps_model_name, 
            wps_model_name_id);
    __ProxyDynamic(wps_model_number, std::string, std::string, std::string, wps_model_number,
            wps_model_number_id);
    __ProxyDynamic(wps_serial_number, std::string, std::string, std::string, wps_serial_number,
            wps_serial_number_id);
    __ProxyDynamic(wps_uuid_e, std::string, std::string, std::string, wps_uuid_e,
            wps_uuid_e_id);

    __ProxyDynamicTrackable(location, kis_tracked_location, location, location_id);

    __Proxy(dot11r_mobility, uint8_t, bool, bool, dot11r_mobility);
    __Proxy(dot11r_mobility_domain_id, uint16_t, uint16_t, uint16_t, 
            dot11r_mobility_domain_id);

    __Proxy(dot11e_qbss, uint8_t, bool, bool, dot11e_qbss);
    __Proxy(dot11e_qbss_stations, uint16_t, uint16_t, uint16_t, dot11e_qbss_stations);
    __Proxy(dot11e_qbss_channel_load, double, double, double, dot11e_qbss_channel_load);

    __Proxy(ccx_txpower, uint8_t, unsigned int, unsigned int, ccx_txpower);
    __Proxy(cisco_client_mfp, uint8_t, bool, bool, cisco_client_mfp);

    __ProxyDynamicTrackable(ie_tag_list, tracker_element_vector_double, ie_tag_list, ie_tag_list_id);

    __ProxyDynamicTrackable(ie_tag_content, tracker_element_int_map, ie_tag_content, ie_tag_content_id);

    void set_ietag_content_from_packet(std::shared_ptr<dot11_ie> tags);

protected:
    virtual void register_fields() override;

    virtual void reserve_fields(std::shared_ptr<tracker_element_map> e) override {
        tracker_component::reserve_fields(e);

        if (e != NULL) {
            // If we're inheriting, it's our responsibility to kick submaps and vectors with
            // complex types as well; since they're not themselves complex objects
            if (dot11d_vec != nullptr) {
                for (auto d = dot11d_vec->begin(); d != dot11d_vec->end(); ++d) {
                    auto din =
                        std::make_shared<dot11_11d_tracked_range_info>(dot11d_country_entry_id,
                                std::static_pointer_cast<tracker_element_map>(*d));

                    // And assign it over the same key
                    *d = std::static_pointer_cast<tracker_element>(din);
                }
            }
        }
    }

    std::shared_ptr<tracker_element_string> ssid;
    std::shared_ptr<tracker_element_uint32> ssid_len;

    std::shared_ptr<tracker_element_uint64> ssid_hash;

    std::shared_ptr<tracker_element_string> owe_ssid;
    int owe_ssid_id;

    std::shared_ptr<tracker_element_uint32> owe_ssid_len;
    int owe_ssid_len_id;

    std::shared_ptr<tracker_element_mac_addr> owe_bssid;
    int owe_bssid_id;

    std::shared_ptr<tracker_element_uint8> ssid_beacon;
    std::shared_ptr<tracker_element_uint8> ssid_probe_response;

    // Channel and optional HT center/second center
    std::shared_ptr<tracker_element_string> channel;
    std::shared_ptr<tracker_element_string> ht_mode;
    std::shared_ptr<tracker_element_uint64> ht_center_1;
    std::shared_ptr<tracker_element_uint64> ht_center_2;

    std::shared_ptr<tracker_element_uint64> first_time;
    std::shared_ptr<tracker_element_uint64> last_time;

    std::shared_ptr<tracker_element_string> beacon_info;
    int beacon_info_id;

    std::shared_ptr<tracker_element_uint8> ssid_cloaked;
    std::shared_ptr<tracker_element_uint64> crypt_set;
    std::shared_ptr<tracker_element_uint8> wpa_mfp_required;
    std::shared_ptr<tracker_element_uint8> wpa_mfp_supported;
    std::shared_ptr<tracker_element_double> maxrate;
    std::shared_ptr<tracker_element_uint32> beaconrate;
    std::shared_ptr<tracker_element_uint32> beacons_sec;
    std::shared_ptr<tracker_element_uint32> ietag_checksum;

    // IE tag dot11d country / power restrictions from 802.11d; 
    // deprecated but still in use
    std::shared_ptr<tracker_element_string> dot11d_country;
    int dot11d_country_id;

    std::shared_ptr<tracker_element_vector> dot11d_vec;
    int dot11d_vec_id;
    int dot11d_country_entry_id;

    // WPS components
    std::shared_ptr<tracker_element_uint32> wps_state;
    int wps_state_id;

    std::shared_ptr<tracker_element_string> wps_manuf;
    int wps_manuf_id;

    std::shared_ptr<tracker_element_string> wps_device_name;
    int wps_device_name_id;

    std::shared_ptr<tracker_element_string> wps_model_name;
    int wps_model_name_id;

    std::shared_ptr<tracker_element_string> wps_model_number;
    int wps_model_number_id;

    std::shared_ptr<tracker_element_string> wps_serial_number;
    int wps_serial_number_id;

    std::shared_ptr<tracker_element_byte_array> wps_uuid_e;
    int wps_uuid_e_id;

    std::shared_ptr<kis_tracked_location> location;
    int location_id;

    // 802.11r mobility/fast roaming advertisements
    std::shared_ptr<tracker_element_uint8> dot11r_mobility;
    std::shared_ptr<tracker_element_uint16> dot11r_mobility_domain_id;

    // 802.11e QBSS
    std::shared_ptr<tracker_element_uint8> dot11e_qbss;
    std::shared_ptr<tracker_element_uint16> dot11e_qbss_stations;
    std::shared_ptr<tracker_element_double> dot11e_qbss_channel_load;

    // Cisco CCX
    std::shared_ptr<tracker_element_uint8> ccx_txpower;
    // Cisco frame protection
    std::shared_ptr<tracker_element_uint8> cisco_client_mfp;

    // IE tags present, and order
    std::shared_ptr<tracker_element_vector_double> ie_tag_list;
    int ie_tag_list_id;

    // IE tag contents
    std::shared_ptr<tracker_element_int_map> ie_tag_content;
    int ie_tag_content_id;
    int ie_tag_content_element_id;
};

/* dot11 client
 *
 * Observed behavior as a client of a bssid.  Multiple records may exist
 * if this device has behaved as a client for multiple BSSIDs
 *
 */
class dot11_client : public tracker_component {
public:
    dot11_client() :
        tracker_component() {
        register_fields();
        reserve_fields(NULL);
    }

    dot11_client(int in_id) :
        tracker_component(in_id) {
            register_fields();
            reserve_fields(NULL);
        }

    dot11_client(int in_id, std::shared_ptr<tracker_element_map> e) :
        tracker_component(in_id) {
            register_fields();
            reserve_fields(e);
        }

    dot11_client(const dot11_client *p) :
        tracker_component{p} {
            bssid = tracker_element_clone_adaptor(p->bssid);
            bssid_key = tracker_element_clone_adaptor(p->bssid_key);
            
            first_time = tracker_element_clone_adaptor(p->first_time);
            last_time = tracker_element_clone_adaptor(p->last_time);

            client_type = tracker_element_clone_adaptor(p->client_type);

            dhcp_host_id = p->dhcp_host_id;
            dhcp_vendor_id = p->dhcp_vendor_id;

            tx_cryptset = tracker_element_clone_adaptor(p->tx_cryptset);
            rx_cryptset = tracker_element_clone_adaptor(p->rx_cryptset);

            eap_identity_id = p->eap_identity_id;
            cdp_device_id = p->cdp_device_id;
            cdp_port_id = p->cdp_port_id;

            decrypted = tracker_element_clone_adaptor(p->decrypted);

            ipdata_id = p->ipdata_id;

            datasize = tracker_element_clone_adaptor(p->datasize);
            datasize_retry = tracker_element_clone_adaptor(p->datasize_retry);
            num_fragments = tracker_element_clone_adaptor(p->num_fragments);
            num_retries = tracker_element_clone_adaptor(p->num_retries);

            location_id = p->location_id;

            reserve_fields(nullptr);
        }

    virtual uint32_t get_signature() const override {
        return adler32_checksum("dot11_client");
    }

    virtual std::unique_ptr<tracker_element> clone_type() override {
        using this_t = std::remove_pointer<decltype(this)>::type;
        auto dup = std::unique_ptr<this_t>(new this_t(this));
        return std::move(dup);
    }

    __Proxy(bssid, mac_addr, mac_addr, mac_addr, bssid);
    __Proxy(bssid_key, device_key, device_key, device_key, bssid_key);
    __Proxy(client_type, uint32_t, uint32_t, uint32_t, client_type);

    __Proxy(first_time, uint64_t, time_t, time_t, first_time);
    __Proxy(last_time, uint64_t, time_t, time_t, last_time);

    __ProxyDynamic(dhcp_host, std::string, std::string, std::string, dhcp_host, dhcp_host_id);
    __ProxyDynamic(dhcp_vendor, std::string, std::string, std::string, dhcp_vendor, dhcp_vendor_id);

    __Proxy(tx_cryptset, uint64_t, uint64_t, uint64_t, tx_cryptset);
    __Proxy(rx_cryptset, uint64_t, uint64_t, uint64_t, rx_cryptset);

    __ProxyDynamic(eap_identity, std::string, std::string, std::string, eap_identity, eap_identity_id);

    __ProxyDynamic(cdp_device, std::string, std::string, std::string, cdp_device, cdp_device_id);
    __ProxyDynamic(cdp_port, std::string, std::string, std::string, cdp_port, cdp_port_id);

    __Proxy(decrypted, uint8_t, bool, bool, decrypted);

    __ProxyDynamicTrackable(ipdata, kis_tracked_ip_data, ipdata, ipdata_id);

    __Proxy(datasize, uint64_t, uint64_t, uint64_t, datasize);
    __ProxyIncDec(datasize, uint64_t, uint64_t, datasize);

    __Proxy(datasize_retry, uint64_t, uint64_t, uint64_t, datasize_retry);
    __ProxyIncDec(datasize_retry, uint64_t, uint64_t, datasize_retry);

    __Proxy(num_fragments, uint64_t, uint64_t, uint64_t, num_fragments);
    __ProxyIncDec(num_fragments, uint64_t, uint64_t, num_fragments);

    __Proxy(num_retries, uint64_t, uint64_t, uint64_t, num_retries);
    __ProxyIncDec(num_retries, uint64_t, uint64_t, num_retries);

    __ProxyDynamicTrackable(location, kis_tracked_location, location, location_id);

protected:
    virtual void register_fields() override {
        register_field("dot11.client.bssid", "bssid", &bssid);
        register_field("dot11.client.bssid_key", "key of BSSID record", &bssid_key);
        register_field("dot11.client.first_time", "first time seen", &first_time);
        register_field("dot11.client.last_time", "last time seen", &last_time);
        register_field("dot11.client.type", "type of client", &client_type);
        dhcp_host_id =
            register_dynamic_field("dot11.client.dhcp_host", "dhcp host", &dhcp_host);
        dhcp_vendor_id =
            register_dynamic_field("dot11.client.dhcp_vendor", "dhcp vendor", &dhcp_vendor);
        register_field("dot11.client.tx_cryptset", "bitset of transmitted encryption", &tx_cryptset);
        register_field("dot11.client.rx_cryptset", "bitset of received encryption", &rx_cryptset);
        eap_identity_id = 
            register_dynamic_field("dot11.client.eap_identity", "EAP identity", &eap_identity);
        cdp_device_id = 
            register_dynamic_field("dot11.client.cdp_device", "CDP device", &cdp_device);
        cdp_port_id =
            register_dynamic_field("dot11.client.cdp_port", "CDP port", &cdp_port);
        register_field("dot11.client.decrypted", "client decrypted", &decrypted);
        
        ipdata_id =
            register_dynamic_field("dot11.client.ipdata", "IPv4 information", &ipdata);

        register_field("dot11.client.datasize", "data in bytes", &datasize);
        register_field("dot11.client.datasize_retry", "retry data in bytes", &datasize_retry);
        register_field("dot11.client.num_fragments", "number of fragmented packets", &num_fragments);
        register_field("dot11.client.num_retries", "number of retried packets", &num_retries);

        location_id =
            register_dynamic_field("dot11.client.location", "location", &location);

    }

    std::shared_ptr<tracker_element_mac_addr> bssid;
    std::shared_ptr<tracker_element_device_key> bssid_key;

    std::shared_ptr<tracker_element_uint64> first_time;
    std::shared_ptr<tracker_element_uint64> last_time;

    std::shared_ptr<tracker_element_uint32> client_type;

    std::shared_ptr<tracker_element_string> dhcp_host;
    int dhcp_host_id;

    std::shared_ptr<tracker_element_string> dhcp_vendor;
    int dhcp_vendor_id;

    std::shared_ptr<tracker_element_uint64> tx_cryptset;
    std::shared_ptr<tracker_element_uint64> rx_cryptset;

    std::shared_ptr<tracker_element_string> eap_identity;
    int eap_identity_id;

    std::shared_ptr<tracker_element_string> cdp_device;
    int cdp_device_id;

    std::shared_ptr<tracker_element_string> cdp_port;
    int cdp_port_id;

    std::shared_ptr<tracker_element_uint8> decrypted;

    std::shared_ptr<kis_tracked_ip_data> ipdata;
    int ipdata_id;

    std::shared_ptr<tracker_element_uint64> datasize;
    std::shared_ptr<tracker_element_uint64> datasize_retry;
    std::shared_ptr<tracker_element_uint64> num_fragments;
    std::shared_ptr<tracker_element_uint64> num_retries;

    std::shared_ptr<kis_tracked_location> location;
    int location_id;
};

// Bitset of top-level device types for easy sorting/browsing
#define DOT11_DEVICE_TYPE_UNKNOWN           0
// This device has beaconed
#define DOT11_DEVICE_TYPE_BEACON_AP         (1 << 0)
// This device has acted like an adhoc device
#define DOT11_DEVICE_TYPE_ADHOC             (1 << 1)
// This device has acted like a client
#define DOT11_DEVICE_TYPE_CLIENT            (1 << 2)
// This device appears to be a wired device bridged to wifi
#define DOT11_DEVICE_TYPE_WIRED             (1 << 3)
// WDS distribution network
#define DOT11_DEVICE_TYPE_WDS               (1 << 4)
// Old-school turbocell
#define DOT11_DEVICE_TYPE_TURBOCELL         (1 << 5)
// We haven't seen this device directly but we're guessing it's there
// because something has talked to it over wireless (ie, cts or ack to it)
#define DOT11_DEVICE_TYPE_INFERRED_WIRELESS (1 << 6)
// We haven't seen this device directly but we've seen something talking to it
#define DOT11_DEVICE_TYPE_INFERRED_WIRED    (1 << 7)
// Device has responded to probes, looking like an AP
#define DOT11_DEVICE_TYPE_PROBE_AP          (1 << 8)

// Dot11 device
//
// Device-level data, additional data stored in the client and ssid arrays
class dot11_tracked_device : public tracker_component {
    friend class kis_80211_phy;
public:
    dot11_tracked_device() :
        tracker_component() {

        last_adv_ie_csum = 0;
        last_bss_invalid = 0;
        bss_invalid_count = 0;
        snapshot_next_beacon = false;

        register_fields();
        reserve_fields(NULL);
    }

    dot11_tracked_device(int in_id) :
        tracker_component(in_id) { 

        last_adv_ie_csum = 0;
        last_bss_invalid = 0;
        bss_invalid_count = 0;
        snapshot_next_beacon = false;

        register_fields();
        reserve_fields(NULL);
    }

    dot11_tracked_device(int in_id, std::shared_ptr<tracker_element_map> e) :
        tracker_component(in_id) {

        last_adv_ie_csum = 0;
        last_bss_invalid = 0;
        bss_invalid_count = 0;
        snapshot_next_beacon = false;

        register_fields();
        reserve_fields(e);
    }

    dot11_tracked_device(const dot11_tracked_device *p) :
        tracker_component{p} {

        last_adv_ie_csum = 0;
        last_bss_invalid = 0;
        bss_invalid_count = 0;
        snapshot_next_beacon = false;

        type_set = tracker_element_clone_adaptor(p->type_set);

        client_map_id = p->client_map_id;
        client_map_entry_id = p->client_map_entry_id;
        num_client_aps = tracker_element_clone_adaptor(p->num_client_aps);

        advertised_ssid_map_id = p->advertised_ssid_map_id;
        advertised_ssid_map_entry_id = p->advertised_ssid_map_entry_id;
        num_advertised_ssids = tracker_element_clone_adaptor(p->num_advertised_ssids);

        responded_ssid_map_id = p->responded_ssid_map_id;
        responded_ssid_map_entry_id = p->responded_ssid_map_entry_id;
        num_responded_ssids = tracker_element_clone_adaptor(p->num_responded_ssids);

        probed_ssid_map_id = p->probed_ssid_map_id;
        probed_ssid_map_entry_id = p->probed_ssid_map_entry_id;
        num_probed_ssids = tracker_element_clone_adaptor(p->num_probed_ssids);

        associated_client_map_id = p->associated_client_map_id;
        associated_client_map_entry_id = p->associated_client_map_entry_id;
        num_associated_clients = tracker_element_clone_adaptor(p->num_associated_clients);
        client_disconnects = tracker_element_clone_adaptor(p->client_disconnects);
        client_disconnects_last = tracker_element_clone_adaptor(p->client_disconnects_last);

        last_sequence = tracker_element_clone_adaptor(p->last_sequence);
        bss_timestamp = tracker_element_clone_adaptor(p->bss_timestamp);

        num_fragments = tracker_element_clone_adaptor(p->num_fragments);
        num_retries = tracker_element_clone_adaptor(p->num_retries);

        datasize = tracker_element_clone_adaptor(p->datasize);
        datasize_retry = tracker_element_clone_adaptor(p->datasize_retry);

        last_bssid_id = p->last_bssid_id;

        last_beacon_timestamp = tracker_element_clone_adaptor(p->last_beacon_timestamp);

        wps_m3_count = tracker_element_clone_adaptor(p->wps_m3_count);
        wps_m3_last = tracker_element_clone_adaptor(p->wps_m3_last);

        wpa_key_vec_id = p->wpa_key_vec_id;
        wpa_key_entry_id = p->wpa_key_entry_id;
        wpa_nonce_vec_id = p->wpa_nonce_vec_id;
        wpa_nonce_entry_id = p->wpa_nonce_entry_id;
        wpa_anonce_vec_id = p->wpa_anonce_vec_id;

        wpa_present_handshake = tracker_element_clone_adaptor(p->wpa_present_handshake);

        ssid_beacon_packet_id = p->ssid_beacon_packet_id;
        pmkid_packet_id = p->pmkid_packet_id;

        last_adv_ssid = tracker_element_clone_adaptor(p->last_adv_ssid);

        min_tx_power = tracker_element_clone_adaptor(p->min_tx_power);
        max_tx_power = tracker_element_clone_adaptor(p->max_tx_power);

        supported_channels_id = p->supported_channels_id;

        link_measurement_capable = tracker_element_clone_adaptor(p->link_measurement_capable);
        neighbor_report_capable = tracker_element_clone_adaptor(p->neighbor_report_capable);

        extended_capabilities_list_id = p->extended_capabilities_list_id;

        beacon_fingerprint = tracker_element_clone_adaptor(p->beacon_fingerprint);
        probe_fingerprint = tracker_element_clone_adaptor(p->probe_fingerprint);
        response_fingerprint = tracker_element_clone_adaptor(p->response_fingerprint);

        last_beaconed_ssid_record_id = p->last_beaconed_ssid_record_id;
        last_probed_ssid_record_id = p->last_probed_ssid_record_id;

        reserve_fields(nullptr);
        }

    virtual uint32_t get_signature() const override {
        return adler32_checksum("dot11_tracked_device");
    }

    virtual std::unique_ptr<tracker_element> clone_type() override {
        using this_t = std::remove_pointer<decltype(this)>::type;
        auto dup = std::unique_ptr<this_t>(new this_t(this));
        return std::move(dup);
    }

    static void attach_base_parent(std::shared_ptr<dot11_tracked_device> self, 
            std::shared_ptr<kis_tracked_device_base> parent) {
        parent->insert(self);
    }

    __Proxy(type_set, uint64_t, uint64_t, uint64_t, type_set);
    __ProxyBitset(type_set, uint64_t, type_set);

    __ProxyDynamicTrackable(client_map, tracker_element_mac_map, client_map, client_map_id);

    std::shared_ptr<dot11_client> new_client() {
        return std::make_shared<dot11_client>(client_map_entry_id);
    }
    __Proxy(num_client_aps, uint64_t, uint64_t, uint64_t, num_client_aps);

    __ProxyDynamicTrackableFunc(advertised_ssid_map, tracker_element_hashkey_map, advertised_ssid_map, 
            advertised_ssid_map_id, {advertised_ssid_map->set_as_vector(true);});

    std::shared_ptr<dot11_advertised_ssid> new_advertised_ssid() {
        return std::make_shared<dot11_advertised_ssid>(advertised_ssid_map_entry_id);
    }

    __Proxy(num_advertised_ssids, uint64_t, uint64_t, uint64_t, num_advertised_ssids);

    __ProxyDynamicTrackableFunc(responded_ssid_map, tracker_element_hashkey_map, responded_ssid_map, 
            responded_ssid_map_id, {responded_ssid_map->set_as_vector(true);});

    std::shared_ptr<dot11_advertised_ssid> new_responded_ssid() {
        return std::make_shared<dot11_advertised_ssid>(responded_ssid_map_entry_id);
    }

    __Proxy(num_responded_ssids, uint64_t, uint64_t, uint64_t, num_responded_ssids);

    __ProxyDynamicTrackableFunc(probed_ssid_map, tracker_element_hashkey_map, probed_ssid_map, 
            probed_ssid_map_id, {probed_ssid_map->set_as_vector(true);});

    std::shared_ptr<dot11_probed_ssid> new_probed_ssid() {
        return std::make_shared<dot11_probed_ssid>(probed_ssid_map_entry_id);
    }

    __Proxy(num_probed_ssids, uint64_t, uint64_t, uint64_t, num_probed_ssids);

    __ProxyDynamicTrackable(associated_client_map, tracker_element_mac_map, 
            associated_client_map, associated_client_map_id);

    __Proxy(num_associated_clients, uint64_t, uint64_t, uint64_t, num_associated_clients);

    __Proxy(client_disconnects, uint64_t, uint64_t, uint64_t, client_disconnects);
    __ProxyIncDec(client_disconnects, uint64_t, uint64_t, client_disconnects);

    __Proxy(client_disconnects_last, uint64_t, uint64_t, uint64_t, client_disconnects_last);

    __Proxy(last_sequence, uint64_t, uint64_t, uint64_t, last_sequence);
    __Proxy(bss_timestamp, uint64_t, uint64_t, uint64_t, bss_timestamp);
    time_t last_bss_invalid;
    unsigned int bss_invalid_count;

    __Proxy(num_fragments, uint64_t, uint64_t, uint64_t, num_fragments);
    __ProxyIncDec(num_fragments, uint64_t, uint64_t, num_fragments);

    __Proxy(num_retries, uint64_t, uint64_t, uint64_t, num_retries);
    __ProxyIncDec(num_retries, uint64_t, uint64_t, num_retries);

    __Proxy(datasize, uint64_t, uint64_t, uint64_t, datasize);
    __ProxyIncDec(datasize, uint64_t, uint64_t, datasize);

    __Proxy(datasize_retry, uint64_t, uint64_t, uint64_t, datasize_retry);
    __ProxyIncDec(datasize_retry, uint64_t, uint64_t, datasize_retry);

    __ProxyDynamic(last_bssid, mac_addr, mac_addr, mac_addr, last_bssid, last_bssid_id);

    __Proxy(last_beacon_timestamp, uint64_t, time_t, 
            time_t, last_beacon_timestamp);

    __Proxy(wps_m3_count, uint64_t, uint64_t, uint64_t, wps_m3_count);
    __ProxyIncDec(wps_m3_count, uint64_t, uint64_t, wps_m3_count);

    __Proxy(wps_m3_last, uint64_t, uint64_t, uint64_t, wps_m3_last);

    __ProxyDynamicTrackable(wpa_key_vec, tracker_element_vector, wpa_key_vec, wpa_key_vec_id);
    std::shared_ptr<dot11_tracked_eapol> create_eapol_packet() {
        return std::make_shared<dot11_tracked_eapol>(wpa_key_entry_id);
    }

    __ProxyDynamicTrackable(ssid_beacon_packet, kis_tracked_packet, ssid_beacon_packet, ssid_beacon_packet_id);
    __ProxyDynamicTrackable(pmkid_packet, kis_tracked_packet, pmkid_packet, pmkid_packet_id);

    __Proxy(wpa_present_handshake, uint8_t, uint8_t, uint8_t, wpa_present_handshake);

    __ProxyDynamicTrackable(wpa_nonce_vec, tracker_element_vector, wpa_nonce_vec, wpa_nonce_vec_id);
    __ProxyDynamicTrackable(wpa_anonce_vec, tracker_element_vector, wpa_anonce_vec, wpa_anonce_vec_id);
    std::shared_ptr<dot11_tracked_nonce> create_tracked_nonce() {
        return std::make_shared<dot11_tracked_nonce>(wpa_nonce_entry_id);
    }

    uint32_t get_last_adv_ie_csum() { return last_adv_ie_csum; }
    void set_last_adv_ie_csum(uint32_t csum) { last_adv_ie_csum = csum; }
    std::shared_ptr<dot11_advertised_ssid> get_last_adv_ssid() {
        return last_adv_ssid;
    }
    void set_last_adv_ssid(std::shared_ptr<dot11_advertised_ssid> adv_ssid) {
        last_adv_ssid = adv_ssid;
    }

    virtual void pre_serialize() override {
        if (client_map != nullptr)
            set_num_client_aps(client_map->size());
        else
            set_num_client_aps(0);

        if (advertised_ssid_map != nullptr)
            set_num_advertised_ssids(advertised_ssid_map->size());
        else
            set_num_advertised_ssids(0);

        if (responded_ssid_map != nullptr)
            set_num_responded_ssids(responded_ssid_map->size());
        else
            set_num_responded_ssids(0);

        if (probed_ssid_map != nullptr)
            set_num_probed_ssids(probed_ssid_map->size());
        else
            set_num_probed_ssids(0);

        if (associated_client_map != nullptr)
            set_num_associated_clients(associated_client_map->size());
        else
            set_num_associated_clients(0);
    }

    __Proxy(min_tx_power, uint8_t, unsigned int, unsigned int, min_tx_power);
    __Proxy(max_tx_power, uint8_t, unsigned int, unsigned int, max_tx_power);
    __ProxyDynamicTrackable(supported_channels, tracker_element_vector_double, 
            supported_channels, supported_channels_id);

    __Proxy(link_measurement_capable, uint8_t, bool, bool, link_measurement_capable);
    __Proxy(neighbor_report_capable, uint8_t, bool, bool, neighbor_report_capable);
    __ProxyDynamicTrackable(extended_capabilities_list, tracker_element_vector_string, 
            extended_capabilities_list, extended_capabilities_list_id);

    __Proxy(beacon_fingerprint, uint32_t, uint32_t, uint32_t, beacon_fingerprint);
    __Proxy(probe_fingerprint, uint32_t, uint32_t, uint32_t, probe_fingerprint);
    __Proxy(response_fingerprint, uint32_t, uint32_t, uint32_t, response_fingerprint);

    bool get_snap_next_beacon() { return snapshot_next_beacon && ssid_beacon_packet == nullptr; }
    void set_snap_next_beacon(bool b) { snapshot_next_beacon = b; }
    bool get_beacon_packet_present() { return ssid_beacon_packet != nullptr; }

    bool get_pmkid_needed() { return pmkid_packet == nullptr; }
    bool get_pmkid_present() { return pmkid_packet != nullptr; }

    __ProxyDynamicTrackable(last_beaconed_ssid_record, tracker_element_alias, 
            last_beaconed_ssid_record, last_beaconed_ssid_record_id);

    __ProxyDynamicTrackable(last_probed_ssid_record, tracker_element_alias, 
            last_probed_ssid_record, last_probed_ssid_record_id);

protected:

    virtual void register_fields() override {
        register_field("dot11.device.typeset", "bitset of device type", &type_set);

        client_map_id =
            register_dynamic_field("dot11.device.client_map", "client behavior", &client_map);

        client_map_entry_id =
            register_field("dot11.device.client",
                    tracker_element_factory<dot11_client>(),
                    "client behavior record");

        register_field("dot11.device.num_client_aps", "number of APs connected to", &num_client_aps);

        // Advertised SSIDs keyed by ssid checksum
        advertised_ssid_map_id = 
            register_dynamic_field("dot11.device.advertised_ssid_map", "advertised SSIDs", &advertised_ssid_map);

        advertised_ssid_map_entry_id =
            register_field("dot11.device.advertised_ssid",
                    tracker_element_factory<dot11_advertised_ssid>(),
                    "advertised SSID");

        register_field("dot11.device.num_advertised_ssids", 
                "number of advertised SSIDs", &num_advertised_ssids);


        // Responded SSIDs keyed by ssid checksum, using the same structure as advertised
        responded_ssid_map_id = 
            register_dynamic_field("dot11.device.responded_ssid_map", "responded SSIDs", &responded_ssid_map);

        responded_ssid_map_entry_id =
            register_field("dot11.device.responded_ssid",
                    tracker_element_factory<dot11_advertised_ssid>(),
                    "responded SSID");

        register_field("dot11.device.num_responded_ssids", 
                "number of responded SSIDs", &num_responded_ssids);


        // Probed SSIDs keyed by int checksum
        probed_ssid_map_id =
            register_dynamic_field("dot11.device.probed_ssid_map", "probed SSIDs", &probed_ssid_map);

        probed_ssid_map_entry_id =
            register_field("dot11.device.probed_ssid",
                    tracker_element_factory<dot11_probed_ssid>(),
                    "probed ssid");

        register_field("dot11.device.num_probed_ssids", "number of probed SSIDs", &num_probed_ssids);

        associated_client_map_id =
            register_dynamic_field("dot11.device.associated_client_map", "associated clients", &associated_client_map);

        // Key of associated device, indexed by mac address
        associated_client_map_entry_id =
            register_field("dot11.device.associated_client", 
                    tracker_element_factory<tracker_element_device_key>(), "associated client");

        register_field("dot11.device.num_associated_clients", 
                "number of associated clients", &num_associated_clients);

        register_field("dot11.device.client_disconnects", 
                "client disconnects message count", 
                &client_disconnects);
        register_field("dot11.device.client_disconnects_last",
                "client disconnects last message",
                &client_disconnects_last);

        register_field("dot11.device.last_sequence", "last sequence number", &last_sequence);
        register_field("dot11.device.bss_timestamp", "last BSS timestamp", &bss_timestamp);

        register_field("dot11.device.num_fragments", "number of fragmented packets", &num_fragments);
        register_field("dot11.device.num_retries", "number of retried packets", &num_retries);

        register_field("dot11.device.datasize", "data in bytes", &datasize);
        register_field("dot11.device.datasize_retry", "retried data in bytes", &datasize_retry);

        last_bssid_id =
            register_dynamic_field("dot11.device.last_bssid", "last BSSID", &last_bssid);

        register_field("dot11.device.last_beacon_timestamp",
                "unix timestamp of last beacon frame", 
                &last_beacon_timestamp);

        register_field("dot11.device.wps_m3_count", "WPS M3 message count", &wps_m3_count);
        register_field("dot11.device.wps_m3_last", "WPS M3 last message", &wps_m3_last);

        wpa_key_vec_id = 
            register_dynamic_field("dot11.device.wpa_handshake_list", "WPA handshakes", &wpa_key_vec);

        wpa_key_entry_id =
            register_field("dot11.eapol.key",
                    tracker_element_factory<dot11_tracked_eapol>(),
                    "WPA handshake key");

        wpa_nonce_vec_id =
            register_dynamic_field("dot11.device.wpa_nonce_list", "Previous WPA Nonces", &wpa_nonce_vec);

        wpa_anonce_vec_id =
            register_dynamic_field("dot11.device.wpa_anonce_list", "Previous WPA ANonces", &wpa_anonce_vec);

        register_field("dot11.device.wpa_present_handshake", 
                "handshake sequences seen (bitmask)", &wpa_present_handshake);

        wpa_nonce_entry_id =
            register_field("dot11.device.wpa_nonce",
                    tracker_element_factory<dot11_tracked_nonce>(),
                    "WPA nonce exchange");

        ssid_beacon_packet_id =
            register_dynamic_field("dot11.device.ssid_beacon_packet",
                    "snapshotted beacon packet", &ssid_beacon_packet);

        pmkid_packet_id =
            register_dynamic_field("dot11.device.pmkid_packet",
                    "snapshotted RSN PMKID packet", &pmkid_packet);

        register_field("dot11.device.min_tx_power", "Minimum advertised TX power", &min_tx_power);
        register_field("dot11.device.max_tx_power", "Maximum advertised TX power", &max_tx_power);

        supported_channels_id =
            register_dynamic_field("dot11.device.supported_channels", "Advertised supported channels", 
                &supported_channels);

        register_field("dot11.device.link_measurement_capable", 
                "Advertised link measurement client capability", &link_measurement_capable);
        register_field("dot11.device.neighbor_report_capable",
                "Advertised neighbor report capability", &neighbor_report_capable);
        
        extended_capabilities_list_id =
            register_dynamic_field("dot11.device.extended_capabilities", 
                "Advertised extended capabilities list", &extended_capabilities_list);

        register_field("dot11.device.beacon_fingerprint", "Beacon fingerprint", &beacon_fingerprint);
        register_field("dot11.device.probe_fingerprint", "Probe (Client->AP) fingerprint", &probe_fingerprint);
        register_field("dot11.device.response_fingerprint", "Response (AP->Client) fingerprint", 
                &response_fingerprint);

        last_beaconed_ssid_record_id =
            register_dynamic_field("dot11.device.last_beaconed_ssid_record", 
                    "last beaconed ssid, complete record", &last_beaconed_ssid_record);
        last_probed_ssid_record_id =
            register_dynamic_field("dot11.device.last_probed_ssid_record", 
                    "last probed ssid, complete record", &last_probed_ssid_record);
    }

    virtual void reserve_fields(std::shared_ptr<tracker_element_map> e) override {
        tracker_component::reserve_fields(e);

        if (e != NULL) {
            // If we're inheriting, it's our responsibility to kick submap and vecs with
            // complex types as well; since they're not themselves complex objects
            for (auto as : *advertised_ssid_map) {
                auto assid =
                    std::make_shared<dot11_advertised_ssid>(advertised_ssid_map_entry_id, 
                            std::static_pointer_cast<tracker_element_map>(as.second));
                as.second = assid;
            }

            if (probed_ssid_map != nullptr) {
                for (auto ps : *probed_ssid_map) {
                    auto pssid =
                        std::make_shared<dot11_probed_ssid>(probed_ssid_map_entry_id, 
                                std::static_pointer_cast<tracker_element_map>(ps.second));
                    ps.second = pssid;
                }
            }

            if (client_map != nullptr) {
                for (auto ci : *client_map) {
                    auto cli =
                        std::make_shared<dot11_client>(client_map_entry_id, 
                                std::static_pointer_cast<tracker_element_map>(ci.second));
                    ci.second = cli;
                }
            }

            // We don't have to deal with the client map because it's a map of
            // simplistic types

            if (wpa_key_vec != nullptr) {
                for (auto k = wpa_key_vec->begin(); k != wpa_key_vec->end(); ++k) {
                    auto eap =
                        std::make_shared<dot11_tracked_eapol>(wpa_key_entry_id, 
                                std::static_pointer_cast<tracker_element_map>(*k));
                    *k = eap;
                }
            }

            if (wpa_nonce_vec != nullptr) {
                for (auto k = wpa_nonce_vec->begin(); k != wpa_nonce_vec->end(); ++k) {
                    auto nonce =
                        std::make_shared<dot11_tracked_nonce>(wpa_nonce_entry_id, 
                                std::static_pointer_cast<tracker_element_map>(*k));
                    *k = nonce;
                }
            }

            if (wpa_anonce_vec != nullptr) {
                for (auto k = wpa_anonce_vec->begin(); k != wpa_anonce_vec->end(); ++k) {
                    auto anonce =
                        std::make_shared<dot11_tracked_nonce>(wpa_nonce_entry_id, 
                                std::static_pointer_cast<tracker_element_map>(*k));
                    *k = anonce;
                }
            }
        }
    }

    // Do we need to snap the next beacon because we're trying to add a beacon
    // record to eapol or pmkid?
    std::atomic<bool> snapshot_next_beacon;

    std::shared_ptr<tracker_element_uint64> type_set;

    std::shared_ptr<tracker_element_mac_map> client_map;
    int client_map_id;
    int client_map_entry_id;
    std::shared_ptr<tracker_element_uint64> num_client_aps;

    std::shared_ptr<tracker_element_hashkey_map> advertised_ssid_map;
    int advertised_ssid_map_id;
    int advertised_ssid_map_entry_id;
    std::shared_ptr<tracker_element_uint64> num_advertised_ssids;

    std::shared_ptr<tracker_element_hashkey_map> responded_ssid_map;
    int responded_ssid_map_id;
    int responded_ssid_map_entry_id;
    std::shared_ptr<tracker_element_uint64> num_responded_ssids;

    std::shared_ptr<tracker_element_hashkey_map> probed_ssid_map;
    int probed_ssid_map_id;
    int probed_ssid_map_entry_id;
    std::shared_ptr<tracker_element_uint64> num_probed_ssids;

    std::shared_ptr<tracker_element_mac_map> associated_client_map;
    int associated_client_map_id;
    int associated_client_map_entry_id;
    std::shared_ptr<tracker_element_uint64> num_associated_clients;
    std::shared_ptr<tracker_element_uint64> client_disconnects;
    std::shared_ptr<tracker_element_uint64> client_disconnects_last;

    std::shared_ptr<tracker_element_uint64> last_sequence;
    std::shared_ptr<tracker_element_uint64> bss_timestamp;

    std::shared_ptr<tracker_element_uint64> num_fragments;
    std::shared_ptr<tracker_element_uint64> num_retries;

    std::shared_ptr<tracker_element_uint64> datasize;
    std::shared_ptr<tracker_element_uint64> datasize_retry;

    std::shared_ptr<tracker_element_mac_addr> last_bssid;
    int last_bssid_id;

    std::shared_ptr<tracker_element_uint64> last_beacon_timestamp;

    std::shared_ptr<tracker_element_uint64> wps_m3_count;
    std::shared_ptr<tracker_element_uint64> wps_m3_last;

    std::shared_ptr<tracker_element_vector> wpa_key_vec;
    int wpa_key_vec_id;
    int wpa_key_entry_id;

    std::shared_ptr<tracker_element_vector> wpa_nonce_vec;
    int wpa_nonce_vec_id;

    std::shared_ptr<tracker_element_vector> wpa_anonce_vec;
    int wpa_anonce_vec_id;

    std::shared_ptr<tracker_element_uint8> wpa_present_handshake;
    int wpa_nonce_entry_id;

    std::shared_ptr<kis_tracked_packet> ssid_beacon_packet;
    int ssid_beacon_packet_id;

    std::shared_ptr<kis_tracked_packet> pmkid_packet;
    int pmkid_packet_id;

    // Un-exposed internal tracking options
    uint32_t last_adv_ie_csum;
    std::shared_ptr<dot11_advertised_ssid> last_adv_ssid;

    // Advertised in association requests but device-centric
    std::shared_ptr<tracker_element_uint8> min_tx_power;
    std::shared_ptr<tracker_element_uint8> max_tx_power;

    std::shared_ptr<tracker_element_vector_double> supported_channels;
    int supported_channels_id;

    std::shared_ptr<tracker_element_uint8> link_measurement_capable;
    std::shared_ptr<tracker_element_uint8> neighbor_report_capable;

    std::shared_ptr<tracker_element_vector_string> extended_capabilities_list;
    int extended_capabilities_list_id;

    std::shared_ptr<tracker_element_uint32> beacon_fingerprint;
    std::shared_ptr<tracker_element_uint32> probe_fingerprint;
    std::shared_ptr<tracker_element_uint32> response_fingerprint;

    int last_beaconed_ssid_record_id;
    std::shared_ptr<tracker_element_alias> last_beaconed_ssid_record;

    int last_probed_ssid_record_id;
    std::shared_ptr<tracker_element_alias> last_probed_ssid_record;
};

#endif

