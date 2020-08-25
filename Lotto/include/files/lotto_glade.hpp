#ifndef LOTTO_GLADE_HPP_
#define LOTTO_GLADE_HPP_

#include <string>

const std::string lotto_glade = R"glade(
<?xml version="1.0" encoding="UTF-8"?>
<!-- Generated with glade 3.22.2 -->
<interface>
  <requires lib="gtk+" version="3.12"/>
  <object class="GtkWindow" id="main_window">
    <property name="can_focus">False</property>
    <child type="titlebar">
      <placeholder/>
    </child>
    <child>
      <object class="GtkBox" id="main_box">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="orientation">vertical</property>
        <child>
          <object class="GtkLabel" id="title_label">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="margin_top">10</property>
            <property name="margin_bottom">10</property>
            <property name="label" translatable="yes">LOTTO</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkGrid" id="lotto_info_grid">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="row_homogeneous">True</property>
            <property name="column_homogeneous">True</property>
            <child>
              <object class="GtkLabel" id="draw_name_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">DRAW</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="draw_value_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="jackpot_name_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">JACKPOT</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="jackpot_value_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">1</property>
          </packing>
        </child>
        <child>
          <object class="GtkSeparator" id="upper_separator">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="margin_top">10</property>
            <property name="margin_bottom">10</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">2</property>
          </packing>
        </child>
        <child>
          <object class="GtkLabel" id="info_label">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="margin_bottom">10</property>
            <property name="label" translatable="yes">CHOOSE 6 NUMBERS:</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">3</property>
          </packing>
        </child>
        <child>
          <object class="GtkGrid" id="numbers_grid">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="row_homogeneous">True</property>
            <property name="column_homogeneous">True</property>
            <child>
              <object class="GtkToggleButton" id="togglebutton_1">
                <property name="label" translatable="yes">1</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_2">
                <property name="label" translatable="yes">2</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_3">
                <property name="label" translatable="yes">3</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">2</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_4">
                <property name="label" translatable="yes">4</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">3</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_5">
                <property name="label" translatable="yes">5</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">4</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_6">
                <property name="label" translatable="yes">6</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">5</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_7">
                <property name="label" translatable="yes">7</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">6</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_8">
                <property name="label" translatable="yes">8</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_9">
                <property name="label" translatable="yes">9</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_10">
                <property name="label" translatable="yes">10</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">2</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_11">
                <property name="label" translatable="yes">11</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">3</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_12">
                <property name="label" translatable="yes">12</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">4</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_13">
                <property name="label" translatable="yes">13</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">5</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_14">
                <property name="label" translatable="yes">14</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">6</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_15">
                <property name="label" translatable="yes">15</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_16">
                <property name="label" translatable="yes">16</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_17">
                <property name="label" translatable="yes">17</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">2</property>
                <property name="top_attach">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_18">
                <property name="label" translatable="yes">18</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">3</property>
                <property name="top_attach">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_19">
                <property name="label" translatable="yes">19</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">4</property>
                <property name="top_attach">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_20">
                <property name="label" translatable="yes">20</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">5</property>
                <property name="top_attach">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_21">
                <property name="label" translatable="yes">21</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">6</property>
                <property name="top_attach">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_22">
                <property name="label" translatable="yes">22</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">3</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_23">
                <property name="label" translatable="yes">23</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">3</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_24">
                <property name="label" translatable="yes">24</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">2</property>
                <property name="top_attach">3</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_25">
                <property name="label" translatable="yes">25</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">3</property>
                <property name="top_attach">3</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_26">
                <property name="label" translatable="yes">26</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">4</property>
                <property name="top_attach">3</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_27">
                <property name="label" translatable="yes">27</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">5</property>
                <property name="top_attach">3</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_28">
                <property name="label" translatable="yes">28</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">6</property>
                <property name="top_attach">3</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_29">
                <property name="label" translatable="yes">29</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">4</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_30">
                <property name="label" translatable="yes">30</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">4</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_31">
                <property name="label" translatable="yes">31</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">2</property>
                <property name="top_attach">4</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_32">
                <property name="label" translatable="yes">32</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">3</property>
                <property name="top_attach">4</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_33">
                <property name="label" translatable="yes">33</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">4</property>
                <property name="top_attach">4</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_34">
                <property name="label" translatable="yes">34</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">5</property>
                <property name="top_attach">4</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_35">
                <property name="label" translatable="yes">35</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">6</property>
                <property name="top_attach">4</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_36">
                <property name="label" translatable="yes">36</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">5</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_37">
                <property name="label" translatable="yes">37</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">5</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_38">
                <property name="label" translatable="yes">38</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">2</property>
                <property name="top_attach">5</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_39">
                <property name="label" translatable="yes">39</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">3</property>
                <property name="top_attach">5</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_40">
                <property name="label" translatable="yes">40</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">4</property>
                <property name="top_attach">5</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_41">
                <property name="label" translatable="yes">41</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">5</property>
                <property name="top_attach">5</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_42">
                <property name="label" translatable="yes">42</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">6</property>
                <property name="top_attach">5</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_43">
                <property name="label" translatable="yes">43</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">6</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_44">
                <property name="label" translatable="yes">44</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">6</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_45">
                <property name="label" translatable="yes">45</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">2</property>
                <property name="top_attach">6</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_46">
                <property name="label" translatable="yes">46</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">3</property>
                <property name="top_attach">6</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_47">
                <property name="label" translatable="yes">47</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">4</property>
                <property name="top_attach">6</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_48">
                <property name="label" translatable="yes">48</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">5</property>
                <property name="top_attach">6</property>
              </packing>
            </child>
            <child>
              <object class="GtkToggleButton" id="togglebutton_49">
                <property name="label" translatable="yes">49</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="left_attach">6</property>
                <property name="top_attach">6</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">4</property>
          </packing>
        </child>
        <child>
          <object class="GtkSeparator" id="lower_sparator">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="margin_top">10</property>
            <property name="margin_bottom">10</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">5</property>
          </packing>
        </child>
        <child>
          <object class="GtkButton" id="run_button">
            <property name="label" translatable="yes">RUN</property>
            <property name="visible">True</property>
            <property name="can_focus">True</property>
            <property name="receives_default">True</property>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">7</property>
          </packing>
        </child>
        <child>
          <object class="GtkGrid" id="result_grid">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="margin_top">10</property>
            <property name="margin_bottom">10</property>
            <property name="row_homogeneous">True</property>
            <property name="column_homogeneous">True</property>
            <child>
              <object class="GtkLabel" id="result_name_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">RESULT</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="result_value_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="matched_name_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">MATCHED</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="matched_value_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="next_jackpot_name_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label" translatable="yes">NEXT JACKPOT</property>
              </object>
              <packing>
                <property name="left_attach">0</property>
                <property name="top_attach">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkLabel" id="next_jackpot_value_label">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
              </object>
              <packing>
                <property name="left_attach">1</property>
                <property name="top_attach">2</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">7</property>
          </packing>
        </child>
        <child>
          <object class="GtkBox" id="buttons_box">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="homogeneous">True</property>
            <child>
              <object class="GtkButton" id="next_button">
                <property name="label" translatable="yes">NEXT DRAW</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkButton" id="close_button">
                <property name="label" translatable="yes">CLOSE</property>
                <property name="visible">True</property>
                <property name="can_focus">True</property>
                <property name="receives_default">True</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="expand">False</property>
            <property name="fill">True</property>
            <property name="position">9</property>
          </packing>
        </child>
      </object>
    </child>
  </object>
</interface>
)glade";

#endif
