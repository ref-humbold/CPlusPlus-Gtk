#ifndef LOTTO_GLADE_HPP_
#define LOTTO_GLADE_HPP_

#include <string>

const std::string lotto_glade = R"glade(
<?xml version="1.0" encoding="UTF-8"?>
<!-- Generated with glade 3.18.3 -->
<interface>
  <requires lib="gtk+" version="3.12"/>
  <object class="GtkWindow" id="main_window">
    <property name="can_focus">False</property>
    <child>
      <object class="GtkBox" id="main_box">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <property name="orientation">vertical</property>
        <child>
          <placeholder/>
        </child>
        <child>
          <placeholder/>
        </child>
        <child>
          <object class="GtkGrid" id="numbers_grid">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <child>
              <object class="GtkToggleButton" id="togglebutton_A1">
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
              <object class="GtkToggleButton" id="togglebutton_A2">
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
              <object class="GtkToggleButton" id="togglebutton_A3">
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
              <object class="GtkToggleButton" id="togglebutton_A4">
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
              <object class="GtkToggleButton" id="togglebutton_A5">
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
              <object class="GtkToggleButton" id="togglebutton_A6">
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
              <object class="GtkToggleButton" id="togglebutton_A7">
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
              <object class="GtkToggleButton" id="togglebutton_B1">
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
              <object class="GtkToggleButton" id="togglebutton_B2">
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
              <object class="GtkToggleButton" id="togglebutton_B3">
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
              <object class="GtkToggleButton" id="togglebutton_B4">
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
              <object class="GtkToggleButton" id="togglebutton_B5">
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
              <object class="GtkToggleButton" id="togglebutton_B6">
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
              <object class="GtkToggleButton" id="togglebutton_B7">
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
              <object class="GtkToggleButton" id="togglebutton_C1">
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
              <object class="GtkToggleButton" id="togglebutton_C2">
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
              <object class="GtkToggleButton" id="togglebutton_C3">
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
              <object class="GtkToggleButton" id="togglebutton_C4">
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
              <object class="GtkToggleButton" id="togglebutton_C5">
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
              <object class="GtkToggleButton" id="togglebutton_C6">
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
              <object class="GtkToggleButton" id="togglebutton_C7">
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
              <object class="GtkToggleButton" id="togglebutton_D1">
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
              <object class="GtkToggleButton" id="togglebutton_D2">
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
              <object class="GtkToggleButton" id="togglebutton_D3">
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
              <object class="GtkToggleButton" id="togglebutton_D4">
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
              <object class="GtkToggleButton" id="togglebutton_D5">
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
              <object class="GtkToggleButton" id="togglebutton_D6">
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
              <object class="GtkToggleButton" id="togglebutton_D7">
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
              <object class="GtkToggleButton" id="togglebutton_E1">
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
              <object class="GtkToggleButton" id="togglebutton_E2">
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
              <object class="GtkToggleButton" id="togglebutton_E3">
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
              <object class="GtkToggleButton" id="togglebutton_E4">
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
              <object class="GtkToggleButton" id="togglebutton_E5">
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
              <object class="GtkToggleButton" id="togglebutton_E6">
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
              <object class="GtkToggleButton" id="togglebutton_E7">
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
              <object class="GtkToggleButton" id="togglebutton_F1">
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
              <object class="GtkToggleButton" id="togglebutton_F2">
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
              <object class="GtkToggleButton" id="togglebutton_F3">
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
              <object class="GtkToggleButton" id="togglebutton_F4">
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
              <object class="GtkToggleButton" id="togglebutton_F5">
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
              <object class="GtkToggleButton" id="togglebutton_F6">
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
              <object class="GtkToggleButton" id="togglebutton_F7">
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
              <object class="GtkToggleButton" id="togglebutton_G1">
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
              <object class="GtkToggleButton" id="togglebutton_G2">
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
              <object class="GtkToggleButton" id="togglebutton_G3">
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
              <object class="GtkToggleButton" id="togglebutton_G4">
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
              <object class="GtkToggleButton" id="togglebutton_G5">
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
              <object class="GtkToggleButton" id="togglebutton_G6">
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
              <object class="GtkToggleButton" id="togglebutton_G7">
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
            <property name="position">2</property>
          </packing>
        </child>
        <child>
          <placeholder/>
        </child>
        <child>
          <placeholder/>
        </child>
      </object>
    </child>
  </object>
</interface>
)glade";

#endif
