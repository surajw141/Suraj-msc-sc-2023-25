import { useMemo } from "react";
import "./FrameComponent2.css";

const FrameComponent2 = ({
  shippingPreferencesDisplay,
  frameDivDisplay,
  frameDivDisplay1,
  propBackgroundColor,
}) => {
  const sellerAccountCreationStyle = useMemo(() => {
    return {
      display: shippingPreferencesDisplay,
    };
  }, [shippingPreferencesDisplay]);

  const verifyTaxDetailsStyle = useMemo(() => {
    return {
      display: frameDivDisplay,
    };
  }, [frameDivDisplay]);

  const storeNameStyle = useMemo(() => {
    return {
      display: frameDivDisplay1,
    };
  }, [frameDivDisplay1]);

  const yourStoreNameStyle = useMemo(() => {
    return {
      backgroundColor: propBackgroundColor,
    };
  }, [propBackgroundColor]);

  return (
    <div className="ellipse-shape">
      <div className="bank-details-frame">
        <nav className="frame-set">
          <div
            className="seller-account-creation1"
            style={sellerAccountCreationStyle}
          >
            Selle­r accou­nt creat­ion
          </div>
          <div className="seller-account">
            <div className="verify-tax-details" style={verifyTaxDetailsStyle}>
              Verif­y tax detai­ls
            </div>
          </div>
          <div className="seller-account1">
            <div className="store-name" style={storeNameStyle}>
              Store name
            </div>
          </div>
          <div className="shipping-preferences">
            <div className="shipping-preferences1">{`Shipp­ing prefe­rences & Picku­p addre­ss`}</div>
          </div>
          <div className="bank-details">Bank detai­ls</div>
        </nav>
        <div className="dot-series">
          <div className="arrow-series">
            <div className="city-rectangle">
              <img
                className="city-rectangle-child"
                loading="eager"
                alt=""
                src="/arrow-3.svg"
              />
              <img
                className="city-rectangle-item"
                loading="eager"
                alt=""
                src="/arrow-4.svg"
              />
              <img
                className="city-rectangle-inner"
                loading="eager"
                alt=""
                src="/arrow-6.svg"
              />
              <img
                className="city-rectangle-child1"
                loading="eager"
                alt=""
                src="/arrow-6.svg"
              />
            </div>
            <div className="your-store-name1" />
            <div className="your-store-name2" />
            <div className="your-store-name3" style={yourStoreNameStyle} />
            <div className="your-store-name4" />
            <div className="your-store-name5" />
          </div>
        </div>
      </div>
    </div>
  );
};

export default FrameComponent2;
